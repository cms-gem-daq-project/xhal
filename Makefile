SUBPACKAGES := \
        python \
        xhalcore \
        xhalarm

SUBPACKAGES.DEBUG    := $(patsubst %,%.debug,    $(SUBPACKAGES))
SUBPACKAGES.RPM      := $(patsubst %,%.rpm,      $(SUBPACKAGES))
SUBPACKAGES.DOC      := $(patsubst %,%.doc,      $(SUBPACKAGES))
SUBPACKAGES.CLEANRPM := $(patsubst %,%.cleanrpm, $(SUBPACKAGES))
SUBPACKAGES.CLEANDOC := $(patsubst %,%.cleandoc, $(SUBPACKAGES))
SUBPACKAGES.CLEAN    := $(patsubst %,%.clean,    $(SUBPACKAGES))

.PHONY: build clean cleanall cleandoc cleanrpm

build: $(SUBPACKAGES)

all: $(SUBPACKAGES) $(SUBPACKAGES.RPM) $(SUBPACKAGES.DOC)

rpm: $(SUBPACKAGES) $(SUBPACKAGES.RPM)

doc: $(SUBPACKAGES.DOC)

cleanrpm: $(SUBPACKAGES.CLEANRPM)

cleandoc: $(SUBPACKAGES.CLEANDOC)

clean: $(SUBPACKAGES.CLEAN)

cleanall: clean cleandoc cleanrpm

$(SUBPACKAGES):
	$(MAKE) -C $@

$(SUBPACKAGES.RPM): $(SUBPACKAGES)
	$(MAKE) -C $(patsubst %.rpm,%, $@) rpm

$(SUBPACKAGES.DOC):
	$(MAKE) -C $(patsubst %.doc,%, $@) doc

$(SUBPACKAGES.CLEANRPM):
	$(MAKE) -C $(patsubst %.cleanrpm,%, $@) cleanrpm

$(SUBPACKAGES.CLEANDOC):
	$(MAKE) -C $(patsubst %.cleandoc,%, $@) cleandoc

$(SUBPACKAGES.CLEAN):
	$(MAKE) -C $(patsubst %.clean,%, $@) clean

.PHONY: $(SUBPACKAGES) $(SUBPACKAGES.INSTALL) $(SUBPACKAGES.CLEAN) $(SUBPACKAGES.DOC) $(SUBPACKAGES.RPM) $(SUBPACKAGES.CLEANRPM) $(SUBPACKAGES.CLEANDOC)

python:

xhalarm:

xhalcore:

xhalcore.RPM: xhalarm
