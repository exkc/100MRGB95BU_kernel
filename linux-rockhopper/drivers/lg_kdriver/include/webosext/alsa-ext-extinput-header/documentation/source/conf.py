# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import textwrap
import sys
import re
sys.path.insert(0, os.path.abspath('./_ext'))
# see http://fnch.users.sourceforge.net/sphinxindexinsinglehtml.html


# -- Project information -----------------------------------------------------

project = 'alsa-ext-extinput'
copyright = '2019-2020, LGE'
author = 'LGE'

# The full version, including alpha/beta/rc tags
branch  = os.popen('git branch').read().split('\n')
git_path = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
active_branch = ""
for br in branch:
    if '*' in br:
        active_branch = br.split('*')[-1].strip()

if active_branch == 'master':
	release = os.popen('git tag --list --merged HEAD --sort=-taggerdate | grep ^submissions/').read().strip().replace('submissions/', '').split('\n')
	number_regex = re.compile('^[0-9]+$')
	for v in release:
		if(number_regex.match(v) != None):
			release = v
			break
else:
    release = os.popen('git describe').read().strip().replace('submissions/', '').split('-')[0]
version = release
print("version is ",version)

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "globalindex",
    "sphinx.ext.intersphinx",
    "breathe",
    "exhale",
	"sphinx_git",
	"sphinx_panels"
]

html_static_path = ['_static']

html_css_files = [

    'custom.css',

]

intersphinx_mapping = {'v4l-dvb-apis': ('https://linuxtv.org/downloads/v4l-dvb-apis', None)}

breathe_projects = { "doxyxml": "../xml/" }
breathe_default_project = "doxyxml"

exhale_args = {
    # These arguments are required
    "containmentFolder":     "./api",
    "rootFileName":          "index.rst",
    "rootFileTitle":         "API Reference",
    "doxygenStripFromPath":  "../..",

    # Suggested optional arguments

    "createTreeView":        True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    # "treeViewIsBootstrap": True,

    "exhaleExecutesDoxygen": True,

    "exhaleDoxygenStdin": textwrap.dedent('''
        INPUT       = %s
        WARN_IF_UNDOCUMENTED = NO
        PREDEFINED += _ALSA_EXT_LGSE_63_H
    ''' % (os.getenv('LEH_DOC_DOXYGENINPUT', '../../linux')))

    # TIP: for fast build for test (just one file),
    # "export LEH_DOC_DOXYGENINPUT=../../linux/alsa-ext/alsa-ext-aenc.h"
    # or without any header files (for fast and only build documentation without api refs.)
    # "export LEH_DOC_DOXYGENINPUT=none"

}
primary_domain = 'cpp'
highlight_language = 'cpp'

# Add any paths that contain templates here, relative to this directory.
# templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
#html_static_path = ['_static']
tls_verify = False
