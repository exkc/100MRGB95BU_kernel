import os
import re
branch  = os.popen('git branch').read().split('\n')
active_branch = ""
for br in branch:
	if '*' in br:
		active_branch = br.split('*')[-1].strip()
if active_branch == 'master':
    release = os.popen('git tag --list --merged HEAD --sort=-taggerdate | grep ^submissions/').read().strip().replace('submissions/', '').split('\n')
    number_regex = re.compile('^[0-9]+$')
    for v in release:
        if(number_regex.match(v) != None):
            version = v
            break

else:
	version = os.popen('git describe').read().strip().replace('submissions/', '').split('-')[0]
print(version)
