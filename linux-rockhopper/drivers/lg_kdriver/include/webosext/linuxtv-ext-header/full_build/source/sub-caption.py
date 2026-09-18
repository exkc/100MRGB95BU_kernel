#!/usr/bin/env python3
import copy
import os
import sys
import re

def sub_captioning(file_path):
    fr = open(file_path, 'r')
    lines = fr.readlines()
    fr.close()

    subcaption_regrep = re.compile(u'<a class="reference internal" href="[0-9a-zA-Z-_\./]*sub-caption.html">')
    subcaption_main_regrep = re.compile(u'<li class="toctree-l1"><a class="reference internal" href="[0-9a-zA-Z-_\./]*sub-caption.html">')

    fw = open(file_path, 'w')

    for line in lines:
        if "sub-caption" in line:
            if subcaption_main_regrep.search(line):
                if "index.html" in file_path:
                    fw.write('')
                else :
                    fw.write(re.sub('<li class="toctree-l1"><a class="reference internal" href="[0-9a-zA-Z-_\./]*sub-caption.html">', '<br><p class="caption"><h2>', line).replace('/a', '/h2></p'))
            elif subcaption_regrep.search(line):
                if "index.html" in file_path:
                    fw.write('')
                else :
                    fw.write(re.sub('<a class="reference internal" href="[0-9a-zA-Z-_\./]*sub-caption.html">', '<p class="caption">', line).replace('/a', '/p'))
            else:
                print(line)
                fw.write('')
        else :
            fw.write(line)

    fw.close()


if __name__ == "__main__":

    path_build = os.path.join(os.path.dirname(os.path.dirname(os.path.realpath(__file__))), 'build', 'html')

    for parent, _, files in os.walk(path_build):
        for f in files:
            if f.endswith(".html") and "sub-caption" not in f:
                if "api" not in parent:
                    print(os.path.join(parent, f))
                sub_captioning(os.path.join(parent, f))

