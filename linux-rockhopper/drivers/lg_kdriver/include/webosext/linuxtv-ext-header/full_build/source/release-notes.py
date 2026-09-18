#!/usr/bin/env python3
import subprocess

cmd = 'git tag --list --merged HEAD --sort=-taggerdate | grep ^submissions/'
output = subprocess.check_output(cmd, shell=True).decode('utf-8').strip(" \n")

fmt = """
{0}
{1}

{2}
"""

tags = output.split("\n")
for i in range(len(tags) - 1):
    cmd = 'git log --pretty=\"%s by %an\" --abbrev-commit --no-merges {}..{}'.format(tags[i+1], tags[i])
    output = subprocess.check_output(cmd, shell=True).decode('utf-8').split("\n")
    change_log = ""
    for log in output:
      if log.strip()=="":
        continue
      commit_message = log.split(' by')[0]
      author = log.split('by ')[-1]
      change_log += "| **{}** by {}\n".format(commit_message, author)
    print(fmt.format(tags[i], "-" * len(tags[i]), change_log))

print(fmt.format(tags[i+1], "-" * len(tags[i+1]), "%s" % (tags[i+1])))
print("----\n")