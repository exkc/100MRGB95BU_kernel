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
import json
sys.path.insert(0, os.path.abspath('./_ext'))
import exhale_extension
# see http://fnch.users.sourceforge.net/sphinxindexinsinglehtml.html


# -- Project information -----------------------------------------------------

project = 'LG BSP Implementation Guide'
copyright = '2023-2024, LGE'
author = 'LGE'

# The full version, including alpha/beta/rc tags
branch  = os.popen('git branch').read().split('\n')
active_branch = ""
for br in branch:
    if '*' in br:
        active_branch = br.split('*')[-1].strip()

fr = open(os.path.join(os.path.dirname(os.path.realpath(__file__)), 'version.json'), 'r')
data_dict = json.load(fr)
version = str(data_dict['version'])
fr.close()
    
print(version)

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

intersphinx_mapping = {'v4l-dvb-apis': ('https://linuxtv.org/downloads/v4l-dvb-apis', None)}

breathe_projects = {
    "linux":     "../xml/",
    "hal":  "../xml/",
    "api":  "../xml/"
}
breathe_default_project = "linux"
html_static_path = ['_static']
html_css_files = [
    'custom.css',
]

# Setup the Exhale extension
exhale_args = {
    'verboseBuild': True,
    "rootFileTitle":        "Unknown",
    "containmentFolder":    "Unknown",

    # These arguments are required
    "rootFileName":          "index.rst",
    "doxygenStripFromPath":  "../..",
    # Suggested optional arguments
    "createTreeView":        True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    # "treeViewIsBootstrap": True,
    "exhaleExecutesDoxygen": True,
    #"exhaleUseDoxyfile":     True,
    "exhaleDoxygenStdin":    " WARN_IF_UNDOCUMENTED = NO  PREDEFINED += _ALSA_EXT_LGSE_63_H",
}

exhale_projects_args = {
    "linux": {
        "exhaleDoxygenStdin":  textwrap.dedent('''
            INPUT       = %s
        ''' % ('./part2/linuxtv-ext-header/linux ./part2/dvbv5-ext-header/linux ./part2/alsa-ext-broadcast-header/linux \
            ./part2/alsa-ext-extinput-header/linux ./part2/alsa-ext-renderer-header/linux ./part2/alsa-ext-soundengine-header/linux \
                ./part2/v4l2-ext-broadcast-header/linux ./part2/v4l2-ext-extinput-header/linux ./part2/v4l2-ext-renderer-header/linux'+exhale_args["exhaleDoxygenStdin"])),
        "containmentFolder":    "./api/linux_api",
        "rootFileTitle":        "API Reference",
    },
    "hal": {
        "exhaleDoxygenStdin":  textwrap.dedent('''
            INPUT       = %s
        ''' % ('./part3/hal-libs-header/hal_inc ./part3/hal-libs-broadcast-header/hal_inc'+exhale_args["exhaleDoxygenStdin"])),
        "containmentFolder":    "./api/hal_api",
        "rootFileTitle":        "API Reference",
    },
    "api": {
        "exhaleDoxygenStdin":  textwrap.dedent('''
            INPUT       = %s
        ''' % ('./part2/linuxtv-ext-header/linux ./part2/dvbv5-ext-header/linux ./part2/alsa-ext-broadcast-header/linux \
            ./part2/alsa-ext-extinput-header/linux ./part2/alsa-ext-renderer-header/linux ./part2/alsa-ext-soundengine-header/linux \
                ./part2/v4l2-ext-broadcast-header/linux ./part2/v4l2-ext-extinput-header/linux ./part2/v4l2-ext-renderer-header/linux \
                    ./part3/hal-libs-header/hal_inc ./part3/hal-libs-broadcast-header/hal_inc' +exhale_args["exhaleDoxygenStdin"] )),
        "containmentFolder":    "./api",
        "rootFileTitle":        "API Reference",
    }
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

html_theme_options = {
    "navigation_depth": 5
}