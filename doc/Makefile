# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS?=
SPHINXBUILD?=sphinx-build
SOURCEDIR=source
BUILDDIR=build

export DOXYREST_PREFIX?=$(CONDA_PREFIX)

export EOS_SITE_NAME?=test-gemdaq-ci
export EOS_SITE_PATH?=/tmp/$(USER)/$(EOS_SITE_NAME)
export EOS_SITE_URL?=https://$(EOS_SITE_NAME).web.cern.ch/$(EOS_SITE_NAME)
export GEM_DOCS_URL?=$(EOS_SITE_URL)

export PYTHONSOURCE=$(shell dirname `pwd`)/python/reg_interface_gem/pkg

.PHONY: help Makefile

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: docs
ifdef USE_DOXYREST
docs: doxyrest
else
docs: doxygen
endif
docs: html

.PHONY: doxygen doxyrest
doxygen:
	cp xhal.cfg.in xhal.cfg
	perl -pi -e "s|__GIT_VERSION__|$(GIT_VERSION)|g" xhal.cfg
	doxygen xhal.cfg

doxyrest: doxygen
	cp doxyrest-config.lua.in doxyrest-config.lua
	perl -pi -e "s|__DOXYREST_PREFIX__|$(DOXYREST_PREFIX)|g" doxyrest-config.lua
	doxyrest -c doxyrest-config.lua

.PHONY: cleandoxygen cleandoxyrest cleanexhale
cleandoxygen:
	rm -rf doxybuild

cleandoxyrest:
	rm -rf $(SOURCEDIR)/doxyrest-api

cleanexhale:
	rm -rf exhalebuild
	rm -rf $(SOURCEDIR)/exhale-api

.PHONY: clean cleanall
clean:
	rm -rf $(BUILDDIR)

cleanall: clean cleandoxygen cleandoxyrest cleanexhale
	rm -rf $(SOURCEDIR)/autoapi

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
