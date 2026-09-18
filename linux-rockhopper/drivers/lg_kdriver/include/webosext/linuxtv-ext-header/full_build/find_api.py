#!/usr/bin/env python3
import re
import os
import glob
import json
import subprocess
import shutil
import pymongo
import copy
from git import Repo
from bs4 import BeautifulSoup
from pymongo import MongoClient
from pprint import pprint as pp

source_root_dir = os.path.dirname(os.path.realpath(__file__))

client = MongoClient('10.157.97.248', 27017)
db = client['undocumented_api']
hal_collection = db['hal_list']
linux_collection = db['linux_list']
not_in_header_collection = db['not_in_header_list']
# not_api_linux_collection = db['linux_not_api']

hal_module_to_category = {
    'criu': 'system', 'irb': 'system', 'mmc': 'system', 'sys': 'system',
    'gal': 'graphic',
    'jpeg': 'photo', 'vo': 'photo',
    'airplay': 'security', 'crypto': 'security', 'drm': 'security', 'hdcp2': 'security', 'keymaster': 'security', 'sstr': 'security', 'svp': 'security',
    'acas_lib': 'broadcast', 'ecp': 'broadcast', 'pvr': 'broadcast',
    'ucom': 'other', 'usb': 'other'
}

category_to_path = {
    'alsa-ext-broadcast-header': ['alsa-ext-broadcast-header/documentation/source/alsa-broadcast'],
    'alsa-ext-extinput-header': ['alsa-ext-extinput-header/documentation/source/alsa-extinput'],
    'alsa-ext-renderer-header': ['alsa-ext-renderer-header/documentation/source/alsa-renderer'],
    'alsa-ext-soundengine-header': ['alsa-ext-soundengine-header/documentation/source/alsa-soundengine'],
    'dvbv5-ext-header': ['dvbv5-ext-header/documentation/source/dvbv5'],
    'linuxtv-ext-header': [
        'linuxtv-ext-header/documentation/source/common-io',
        'linuxtv-ext-header/documentation/source/graphics',
        'linuxtv-ext-header/documentation/source/media',
        'linuxtv-ext-header/documentation/source/other',
        'linuxtv-ext-header/documentation/source/power-management',
        'linuxtv-ext-header/documentation/source/system'
    ],
    'v4l2-ext-broadcast-header': ['v4l2-ext-broadcast-header/documentation/source/broadcast'],
    'v4l2-ext-extinput-header': ['v4l2-ext-extinput-header/documentation/source/extinput'],
    'v4l2-ext-renderer-header': ['v4l2-ext-renderer-header/documentation/source/renderer']
}

def get_module_name(file_path, api):
    file_name = os.path.basename(file_path)
    if 'acas__lib' in file_name:
        return 'acas_lib'
    if 'v4l2-ext-earc_' in file_name:
        return 'hdmi-earc'
    if '_fb-ext' in file_name:
        return 'framebuffer'
    if 'v4l2-ext-vbe_' in file_name:
        return 'panel-controller'

    if api == 'hal':
        match = re.search(r'function_hal__(.*?)_8h_', file_name)
        if match:
            return match.group(1)
        else:
            print('file_name: ', file_name)
            return None
    elif api == 'linux':
        match = re.search(r'define_(.*?)(?:-ext-(.*?))?(?:_8h_|$)', file_name)
        if match:
            if 'displayport' in match.group():
                return 'displayport' if 'alsa-ext' in match.group() else 'displayport-input'
            elif 'hdmi' in match.group():
                return 'hdmi' if 'alsa-ext' in match.group() else 'hdmi-input'
            return match.group(2) if match.group(2) else match.group(1)
        else:
            print('file_name: ', file_name)
            return None

def get_function_name(file):
    with open(file, 'r') as html_file:
        soup = BeautifulSoup(html_file, 'html.parser')
        title = soup.title.string
        function_name = title.split(' ')[1]
        return function_name

def save_to_db(collection, function_list):
    collection.delete_many({})
    for function_info in function_list:
        if not collection.find_one({
            "category": function_info["category"],
            "module": function_info["module"],
            "function": function_info["function"]
        }):
            collection.insert_one(function_info)

def get_json(path):
    with open(path, 'r') as file:
        data_dict = json.load(file)
    return data_dict

def find_h_file():
    git_dict = get_json(os.path.join(source_root_dir, 'source/git-repository.json'))
    header_files = {}
    header_files_dir = []

    for git, info in git_dict.items():
        if info["part"] == "part2":
            if git not in header_files:
                header_files[git] = {}
            h_dir = os.path.join(source_root_dir, "source/part2", git, 'linux') # 헤더 경로
            if git == 'linuxtv-ext-header':
                h_dir_fb_ext = os.path.join(h_dir, 'fb-ext')
                h_dir_voice_ext = os.path.join(h_dir, 'voice-ext')
                h_dir = [h_dir_fb_ext, h_dir_voice_ext]
            else:
                h_dir = [h_dir]

            for h in h_dir:
                for root, dirs, files in os.walk(h):
                    for file in files:
                        if file.endswith('.h'):
                            h_file = file
                            header_files[git][h_file.split('.h')[0]] = []
                            header_files_dir.append(os.path.join(root, h_file))
    # pp(header_files)
    # print('---------------')
    # print(header_files_dir)
    return header_files, header_files_dir

def is_api(line):
    api_keywords = ['@brief', '@param', '@return']
    api_keywords2 = ['Functions & Parameters', 'control id']
    api_keywords3 = ['Functions & Parameters', 'Return Value']
    return all(keyword in line for keyword in api_keywords) or all(keyword in line for keyword in api_keywords2) or all(keyword in line for keyword in api_keywords3)

def find_real_api(header_files, header_files_dir):
    real_api = copy.deepcopy(header_files)
    not_api = copy.deepcopy(header_files)


    for header_file_dir in header_files_dir:
        with open(header_file_dir, 'r') as h:
            lines = h.readlines()
        tmp = ''
        for line in lines:
            stripped = line.strip()
            if stripped.startswith('/**'):
                record_start = True
            if record_start:
                tmp += stripped
            if stripped.startswith('#define'):
                if stripped.split(' ')[1] == '__user':
                    continue
                header_file_name = header_file_dir.split('/')[-1].split('.h')[0]
                for git in header_files.keys():
                    for module in header_files[git].keys():
                        if module == 'voice-ext':
                            continue
                        if header_file_name == module:
                            if is_api(tmp):
                                real_api[git][module].append(stripped.split(' ')[1])
                            else:
                                not_api[git][module].append(stripped.split(' ')[1])
                record_start = False
                tmp = ''

    # pp(header_files)
    return real_api, not_api


def linux_parser():

    header_files, header_files_dir = find_h_file() # 딕셔너리, 리스트

    real_api, not_api = find_real_api(header_files, header_files_dir) # 딕셔너리

    linux_function_list = []
    # linux_not_api_list = []
    function_list_in_rst = []

    for git, module_dict in real_api.items():
        paths = category_to_path.get(git)
        for path in paths:
            git_dir = os.path.join(source_root_dir, 'source/part2', path)
            print('git_dir', git_dir)
            for root, dirs, files in os.walk(git_dir):
                for file in files:
                    if file.endswith('.rst'):
                        rst_file = os.path.join(git_dir, file)

                        if os.path.exists(rst_file):
                            with open(rst_file, 'r') as f:
                                content = f.readlines() # content는 리스트
                                # function_list_in_rst = []
                                for line in content:
                                    function_name = ''
                                    if ':c:macro:' in line or ':func:' in line:
                                        function_name = line.split('`')[1].strip()
                                    elif ':ref:' in line:
                                        function_name = line.split('`')[1]
                                        if '<v4l-dvb-apis' in function_name or '<v4l2-' in function_name or '<dvbv5' in function_name:
                                            function_name = function_name.split('<')[0].strip()
                                            if 'ioctl' in function_name:
                                                function_name = function_name.split('ioctl')[1].strip()
                                            if ',' in function_name:
                                                function_name = function_name.split(',')
                                        elif 'v4l-dvb-apis' in function_name:
                                            function_name = function_name.split(':')[1].strip()
                                    elif '<https://' in line:
                                        function_name = line.replace('`', '').replace('	', ' ').split(" <")[0].split(' ')[-1].replace('()', '')
                                    # print(function_name)
                                    if function_name:
                                        function_list_in_rst.append(function_name) # rst에 있는 함수 저장
                                        # print('function_name', function_name)

        # function_list_in_rst = list(set(function_list_in_rst))
                        else:
                            print(f'{rst_file} not found')

    for git, module_dict in real_api.items():
        for module, functions in module_dict.items():
            if functions:
                for function in functions:
                    linux_function_info = {
                        "category": git,
                        "module": module,
                        "function": function,
                        "documented": "Yes" if function in function_list_in_rst else "No"
                    }
                    linux_function_list.append(linux_function_info)

    # for git, module_dict in not_api.items():
    #     for module, functions in module_dict.items():
    #         if functions:
    #             for function in functions:
    #                 linux_not_api_info = {
    #                     "category": git,
    #                     "module": module,
    #                     "function": function,
    #                     "documented": "Yes" if function in function_list_in_rst else "No"
    #                 }
    #                 linux_not_api_list.append(linux_not_api_info)

    save_to_db(linux_collection, linux_function_list)
    # save_to_db(not_api_linux_collection, linux_not_api_list)
    # save_to_db(not_in_header_collection, not_in_header_list)


def hal_parser():
    hal_html_dir = os.path.join(source_root_dir, 'build/html/api/hal_api/')
    html_files = glob.glob(f'{hal_html_dir}/function_hal__*_8h*.html')

    hal_function_names = {}
    hal_function_names['security']= {}
    hal_function_names['security']['keymaster']= []

    # keymaster
    key_master_dir = os.path.join(source_root_dir, "source/part3/hal-libs-header/hal_inc/optee_keymaster3_device.h")
    with open(key_master_dir, 'r') as k:
        lines = k.readlines()
        tmp = ''
        for line in lines:
            stripped = line.strip()
            if stripped.startswith('/**'):
                record_start = True
            if record_start:
                tmp += stripped
            if record_start and stripped.startswith('keymaster_error_t'):
                if '@brief' in tmp:
                    api_name = stripped.split()[1].split('(')[0]
                    hal_function_names['security']['keymaster'].append(api_name)
                record_start = False
                tmp = ''
    # print(hal_function_names)

    for file in html_files:
        module_name = get_module_name(file, 'hal')
        category = hal_module_to_category.get(module_name, 'none')
        function_name = get_function_name(file)

        if category not in hal_function_names:
            hal_function_names[category]= {}
        if module_name not in hal_function_names[category]:
            hal_function_names[category][module_name]= []
        hal_function_names[category][module_name].append(function_name)
    # print(hal_function_names)

    hal_function_list = []

    for category, module_dict in hal_function_names.items():
        for module, functions in module_dict.items():
            if module == 'keymaster':
                print(functions)
            if category == 'broadcast':
                rst_dir = os.path.join(source_root_dir, 'source/part3/hal-libs-broadcast-header/documentation/source/security')
            else:
                rst_dir = os.path.join(source_root_dir, 'source/part3/hal-libs-header/documentation/source/', category)

            rst_file = os.path.join(rst_dir, module + '.rst')

            if os.path.exists(rst_file):
                with open(rst_file, 'r') as f:
                    content = f.readlines() # content는 리스트
                    function_list_in_rst = []
                    for line in content:
                        if ':cpp:func:' in line or ':func:' in line:
                            function_name = line.split('`')[1].strip()
                            if module == 'keymaster':
                                function_name = function_name.split('::')[-1]
                                # print(function_name)
                            function_list_in_rst.append(function_name) # rst에 있는 함수 저장

                    for function in functions:
                        if module == 'keymaster':
                            print(function)
                        hal_function_info = {
                            "category": category,
                            "module": module,
                            "function": function,
                            "documented": "Yes" if function in function_list_in_rst else "No"
                        }
                        hal_function_list.append(hal_function_info)
            else:
                print(f'{rst_file} not found')
    # print(hal_function_list)

    save_to_db(hal_collection, hal_function_list)

if __name__ == "__main__":
    hal_parser()
    linux_parser()
