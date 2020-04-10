# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys

# sys.path.insert(0, os.path.abspath("../../python/reg_interface_gem/"))

if os.getenv("USE_DOXYREST"):
    # path for doxyrest sphinx extensions
    sys.path.insert(
        1, "{:s}/share/doxyrest/sphinx".format(os.getenv("DOXYREST_PREFIX"))
    )

    import doxyrest

import sphinx_rtd_theme

# -- Project information -----------------------------------------------------

project = u"xhal"
author = u"CMS GEM DAQ Project"
copyright = u"2017, {}".format(author)

# The version info for the project you're documenting, acts as replacement for
# |version| and |release|, also used in various other places throughout the
# built documents.
#
# The full version, including alpha/beta/rc tags.
release = os.popen("git describe --abbrev=6 --dirty --always --tags").read().strip()
try:
    release = re.sub("^v", "", release)
except:
    pass  # release = "0.0.0"

# The short X.Y version.
version = "{0}.{1}".format(*release.split("."))  #'1.0'
print("Version {}".format(version))
print("Release {}".format(release))

# -- General configuration ---------------------------------------------------

extensions = [
    "sphinx.ext.doctest",
    "sphinx.ext.intersphinx",
    "sphinx.ext.todo",
    "sphinx.ext.coverage",
    "sphinx.ext.mathjax",
    "sphinx.ext.ifconfig",
    "sphinx.ext.viewcode",
    "sphinxcontrib.srclinks",
    "sphinx.ext.extlinks",
    "sphinxcontrib.napoleon",
    "sphinxcontrib.srclinks",
    # "sphinxcontrib.osexample",
    "sphinx_copybutton",
    "sphinx_tabs.tabs",
    "sphinx_rtd_theme",
    "autoapi.extension",  ## sphinx-autoapi
    # "autoapi.spinx", ## autoapi...
    # "sphinx.ext.autodoc",
    # "sphinx.ext.inheritance_diagram",
]

autoapi_type = "python"
autoapi_python_use_implicit_namespaces = True  ## default False
autoapi_dirs = [
    "{}".format(os.getenv("PYTHONSOURCE")),
]
autoapi_add_toctree_entry = False  ## default True
autoapi_keep_files = True  ## default False
autoapi_options = [
    "members",
    "undoc-members",
    "private-members",
    "show-inheritance",
    "special-members",
    "show-inheritance-diagram",
    "show-module-summary",
]
autoapi_ignore = ["*migrations*", "*conf.py", "*setup.py"]
autoapi_template_dir = "_templates/autoapi"

if os.getenv("USE_DOXYREST"):
    extensions += ["doxyrest", "cpplexer"]

extensions += ["breathe", "exhale"]
breathe_projects = {
    "xhal": "../exhalebuild/xml/",
}

breathe_default_project = "xhal"

# Setup the exhale extension
exhale_args = {
    # These arguments are required
    "containmentFolder": "./exhale-api",
    "rootFileName": "api.rst",
    "rootFileTitle": "{} API documentation".format(project),
    "doxygenStripFromPath": "..",
    # Suggested optional arguments
    "createTreeView": True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    "treeViewIsBootstrap": True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": """
PROJECT_NAME = {}
PROJECT_NUMBER = {}
INPUT = ../../xhalcore/include
PREDEFINED+= DOXYGEN_IGNORE_THIS
""".format(
        project, release
    ),
}

# # Tell sphinx what the primary language being documented is.
# primary_domain = "cpp"

# # Tell sphinx what the pygments highlight language should be.
# highlight_language = "cpp"

# Add any paths that contain templates here, relative to this directory.
templates_path = ["_templates"]

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = ".rst"

# The master toctree document.
master_doc = "index"

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = None

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = "sphinx"

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True

# -- Options for HTML output -------------------------------------------------

html_context = {
    "display_gitlab": True,
    "gitlab_host": "gitlab.cern.ch",
    "gitlab_user": "cms-gem-daq-project",
    "gitlab_repo": "xhal",
    "gitlab_version": "release/legacy-1.0",  ## grab this dynamically
    "conf_py_path": "/doc/source/",
}

html_show_sourcelink = True

## Set an image file to be used as a logo at the top of the sidebar
# html_logo

## Show only the logo at the top of the sidebar
# logo_only

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = "sphinx_rtd_theme"

html_theme_options = {
    "navigation_depth": 50,
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ["_static"]

# Custom CSS
# These paths are either relative to html_static_path
# or fully qualified paths (eg. https://...)
html_css_files = [
    # "{}/css/rtd-custom.css".format(os.getenv("GEM_DOCS_URL")),
    # "css/custom.css",
]

# Custom JavaScript
# These paths are either relative to html_static_path
# or fully qualified paths (eg. https://...)
html_js_files = [
    # 'js/custom.js',
]

intersphinx_mapping = {
    "cmsgemos": (os.getenv("EOS_SITE_URL") + "/docs/api/cmsgemos/latest", None,),
    "gemplotting": (os.getenv("EOS_SITE_URL") + "/docs/api/gemplotting/latest", None,),
    "vfatqc": (os.getenv("EOS_SITE_URL") + "/docs/api/vfatqc/latest", None,),
    "ctp7_modules": (
        os.getenv("EOS_SITE_URL") + "/docs/api/ctp7_modules/latest",
        None,
    ),
    "reg_utils": (os.getenv("EOS_SITE_URL") + "/docs/api/reg_utils/latest", None,),
}
