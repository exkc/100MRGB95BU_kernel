#!/usr/bin/env python3
import subprocess
import os
import json
import shutil
import argparse
import pymongo
import copy

def get_json(path):
    with open(path, 'r') as file:
            data_dict = json.load(file)
    return data_dict

def parsing_argument():
    parser = argparse.ArgumentParser(formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--header', type=str, default='', help="build header")
    parser.add_argument('--fetch', type=str, default='', help="refspec")
    return parser.parse_args()

def get_git_log(prev, post):
    cmd = 'git log --pretty=\"%s by %an\" --abbrev-commit --no-merges {}..{}'.format(prev, post)
    output = subprocess.check_output(cmd, shell=True).decode('utf-8').split("\n")
    change_log = ""
    for log in output:
      if log.strip()=="":
        continue
      commit_message = log.split(' by')[0]
      author = log.split('by ')[-1]
      change_log += "| **{}** by {}\n".format(commit_message, author)

    return change_log

def create_header_submission_history(git_dict):

    source_root_dir = os.path.dirname(os.path.realpath(__file__))

    if os.path.exists(os.path.join(source_root_dir, "release-notes.rst")):
        os.remove(os.path.join(source_root_dir, "release-notes.rst"))
        f = open(os.path.join(source_root_dir, "release-notes.rst"), "w")
        f.write("""Submission History
#################

""")
        f.close()

    for git, info in git_dict.items():

      if "socts" in git:
          continue
      else:
          if not info['build']:
              continue

      release_script_path = os.path.join(source_root_dir, info["part"], git, "documentation/source/release-notes.py")

      shutil.copy(os.path.join(source_root_dir, "release-notes.py"), release_script_path)
      os.chdir(os.path.join(source_root_dir, info["part"], git))
      output = os.popen("python3 {}".format(release_script_path)).read()
      os.remove(release_script_path)
      os.chdir(source_root_dir)

      with open(os.path.join(source_root_dir, "release-notes.rst"),"a") as f:
          section = "{} Submission History".format(git)
          f.write("{}\n{}\n\n".format(section, "=" * len(section)))
          f.write(output)

def create_all_header_submission_history(git_dict):

    client = pymongo.MongoClient(host='10.157.97.248', port=27017)
    db = client['bsp_documentation']
    collection = db["version"]
    newest_data = collection.find({'newest':True})[0]
    newest_version = newest_data['version']

    source_root_dir = os.path.dirname(os.path.realpath(__file__))

    if os.path.exists(os.path.join(source_root_dir, "release-notes.rst")):
        os.remove(os.path.join(source_root_dir, "release-notes.rst"))
        f = open(os.path.join(source_root_dir, "release-notes.rst"), "w")
        f.write("""Submission History
#################

""")
        f.close()

    tmp_newest_data = copy.deepcopy(newest_data)

    for version in range(newest_version, 1, -1):

        with open(os.path.join(source_root_dir, "release-notes.rst"),"a") as f:
            section = "Ver{}..Ver{}".format(version-1, version)
            f.write("{}\n{}\n\n".format(section, "*" * len(section)))

            # add git tag info
            tmp_newest_data.pop('_id', None)
            tmp_newest_data.pop('version', None)
            tmp_newest_data.pop('newest', None)
            cmd1 = "Git Tag Information in version " + str(version)
            cmd2 = ""
            for key, value in tmp_newest_data.items():
                cmd2 += "| '" + key + "': '" + value + "'\n"
            f.write("{}\n{}\n".format(cmd1, '='*len(cmd1)))
            f.write("{}\n".format(cmd2))

        prev_data = collection.find({'version':version-1})[0]
        data = collection.find({'version':version})[0]
        for git, info in git_dict.items():
            if 'socts' in git:
              continue
            if prev_data[git] == data[git]:
              continue

            os.chdir(os.path.join(source_root_dir, info["part"], git))
            change_log = get_git_log(prev_data[git], data[git])
            os.chdir(source_root_dir)

            with open(os.path.join(source_root_dir, "release-notes.rst"),"a") as f:
                section = "{} ({}..{})".format(git, prev_data[git], data[git])
                f.write("{}\n{}\n\n".format(section, "=" * len(section)))
                f.write("{}\n\n".format(change_log))


if __name__ == "__main__":

    args = parsing_argument()
    args.header = (args.header).split('/')[-1]

    git_dict = get_json('source/git-repository.json')

    if args.header == '':
        create_all_header_submission_history(git_dict)
    else:
        create_header_submission_history(git_dict)