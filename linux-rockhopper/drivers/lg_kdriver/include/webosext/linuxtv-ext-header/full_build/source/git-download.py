#!/usr/bin/env python3
import os
import json
import shutil
import pymongo
import argparse
import subprocess
from git import Repo

def get_json(path):
    with open(path, 'r') as file:
        data_dict = json.load(file)
    return data_dict

def set_json(path, text_dict):
    if not os.path.exists(os.path.dirname(path)):
        os.makedirs(os.path.dirname(path))
    with open(path, 'w') as file:
        json.dump(text_dict, file, indent='\t')

def parsing_argument():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--header', type=str, default='', help="build header")
    parser.add_argument('--fetch', type=str, default='', help="refspec")
    return parser.parse_args()

if __name__ == "__main__":

    args = parsing_argument()

    git_dict = get_json('source/git-repository.json')
    git_header_list = list(git_dict.keys())

    client = pymongo.MongoClient(host='10.157.97.248', port=27017)
    db = client['bsp_documentation']
    collection = db["version"]
    newest_data = list(collection.find({'newest':True}, {'_id':False}))
    data = newest_data[0] if newest_data else None
    version_up = False

    args.header = (args.header).split('/')[-1]
    if args.header != '':
        if args.fetch == '':
            print("If you build with certain headers, you should set fetch.")
            exit()

        git_header_list = ["linuxtv-ext-header", "socts"]
        git_header_list.append(args.header)
        git_header_list = list(set(git_header_list))

    else:
        if args.fetch:
            print("If you build with all headers, you can't set fetch.")
            exit()

    for git, info in git_dict.items():
        if git in git_header_list:
            git_dict[git]['build'] = True
            if git == args.header:
                git_dict[git]['fetch'] = args.fetch
            else:
                git_dict[git]['fetch'] = ''
        else:
            git_dict[git]['build'] = False
            git_dict[git]['fetch'] = ''

    set_json('source/git-repository.json', git_dict)

    cmd = 'git config --get user.name'
    user_name = subprocess.check_output(cmd, shell=True).decode('utf-8').strip(" \n")

    source_root_dir = os.path.dirname(os.path.realpath(__file__))


    for git, info in git_dict.items():
        # cloning all git
        if os.path.exists(os.path.join(source_root_dir, info["part"], git)):
            shutil.rmtree(os.path.join(source_root_dir, info["part"], git))

        if not info["build"]:
            continue

        cmd = 'git -C {}/{} clone \"ssh://{}@wall.lge.com:29448/{}\"'.format(source_root_dir, info["part"], user_name, info["repository"])
        subprocess.check_output(cmd, shell=True)
        git_dir = os.path.join(source_root_dir, info["part"], git)
        if info["fetch"] != '':
            cmd = 'cd {} && git pull ssh://{}@wall.lge.com:29448/{} {} && cd {}'.format(git_dir, user_name, info["repository"], info["fetch"], source_root_dir)
            subprocess.check_output(cmd, shell=True)
        if args.header == '':
            repo = Repo(git_dir)
            latest_tag = (repo.git.describe("--abbrev=0")).split('.')[0]
            if "socts" not in git:
                if data[git] != latest_tag:
                    data[git] = latest_tag
                    version_up = True
                cmd = 'cd {} && git checkout {} && cd {}'.format(git_dir, latest_tag, source_root_dir)
                subprocess.check_output(cmd, shell=True)
        cmd = 'find %s -name index.rst -exec rm {} \\;'%git_dir
        subprocess.check_output(cmd, shell=True)
        cmd = 'find %s -name release-notes.rst -exec rm {} \\;'%git_dir
        subprocess.check_output(cmd, shell=True)

        if "socts" not in git:
            cmd = 'find %s/documentation -maxdepth 1 -type f -exec rm -f {} +'%git_dir
            subprocess.check_output(cmd, shell=True)
            cmd = 'find %s/documentation/source -maxdepth 1 -type f -exec rm -f {} +'%git_dir
            subprocess.check_output(cmd, shell=True)

        if git == "linuxtv-ext-header":

            cmd = 'find %s/documentation_foundation -maxdepth 1 -type f -exec rm -f {} +'%git_dir
            subprocess.check_output(cmd, shell=True)

            for root, _, files in os.walk(os.path.join(git_dir, "documentation_foundation", "source")):
                for f in files:
                    if ".py" in f:
                        os.remove(os.path.join(root, f))

            if os.path.exists(os.path.join(git_dir, "full_build")):
                shutil.rmtree(os.path.join(git_dir, "full_build"))

            if os.path.exists(os.path.join(source_root_dir, "part1", git, "documentation_foundation")):
                shutil.rmtree(os.path.join(source_root_dir, "part1", git, "documentation_foundation"))
            shutil.copytree(os.path.join(git_dir, "documentation_foundation"), os.path.join(source_root_dir, "part1", git, "documentation_foundation"))

        elif git == 'socts':

            for root, _, files in os.walk(os.path.join(git_dir, "Documentation", "source")):
                for f in files:
                    if ".py" in f:
                        os.remove(os.path.join(root, f))
                    if "producer-manual" in f:
                        fr = open(os.path.join(root, f), 'r')
                        lines = fr.readlines()
                        fr.close()

                        fw = open(os.path.join(root, f), 'w')
                        for line in lines:
                            if ".. include:: /../../" in line:
                                fw.write(line.replace(".. include:: /../../", ".. include:: /part4/socts/"))
                            else :
                                fw.write(line)
                        fw.close()
    if args.header == '':
        if version_up:
            collection.update_one({'newest':True}, {'$set': {'newest': False}})
            data['version'] = data['version'] + 1
            data['newest'] = True
            collection.insert_one(data)

    set_json('source/version.json', {'version' : data['version']})