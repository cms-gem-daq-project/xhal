SUBPACKAGES := \
        python \
        xhalcore \
        xhalarm

SUBPACKAGES.DEBUG    := $(patsubst %,%.debug,    ${SUBPACKAGES})
SUBPACKAGES.RPM      := $(patsubst %,%.rpm,      ${SUBPACKAGES})
SUBPACKAGES.DOC      := $(patsubst %,%.doc,      ${SUBPACKAGES})
SUBPACKAGES.CLEANRPM := $(patsubst %,%.cleanrpm, ${SUBPACKAGES})
SUBPACKAGES.CLEANDOC := $(patsubst %,%.cleandoc, ${SUBPACKAGES})
SUBPACKAGES.CLEAN    := $(patsubst %,%.clean,    ${SUBPACKAGES})

all: $(SUBPACKAGES) $(SUBPACKAGES.RPM) $(SUBPACKAGES.DOC)

rpm: $(SUBPACKAGES) $(SUBPACKAGES.RPM)

doc: $(SUBPACKAGES.DOC)
	$(MAKE) -C $@ docs

cleanrpm: $(SUBPACKAGES.CLEANRPM)

cleandoc: $(SUBPACKAGES.CLEANDOC)
	$(MAKE) -C doc cleanall

clean: $(SUBPACKAGES.CLEAN) $(SUBPACKAGES.CLEANRPM) $(SUBPACKAGES.CLEANDOC)

$(SUBPACKAGES):
	$(MAKE) -C $@

$(SUBPACKAGES.RPM):
	$(MAKE) -C $(patsubst %.rpm,%, $@) rpm

$(SUBPACKAGES.DOC):
	$(MAKE) -C $(patsubst %.doc,%, $@) doc

$(SUBPACKAGES.CLEANRPM):
	$(MAKE) -C $(patsubst %.cleanrpm,%, $@) cleanrpm

$(SUBPACKAGES.CLEANDOC):
	$(MAKE) -C $(patsubst %.cleandoc,%, $@) cleandoc

$(SUBPACKAGES.CLEAN):
	$(MAKE) -C $(patsubst %.clean,%, $@) clean
