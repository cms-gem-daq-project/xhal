SUBPACKAGES := \
        reg_interface_gem

SUBPACKAGES.DEBUG    := $(patsubst %,%.debug,    $(SUBPACKAGES))
SUBPACKAGES.DOC      := $(patsubst %,%.doc,      $(SUBPACKAGES))
SUBPACKAGES.RPM      := $(patsubst %,%.rpm,      $(SUBPACKAGES))
SUBPACKAGES.CLEANRPM := $(patsubst %,%.cleanrpm, $(SUBPACKAGES))
SUBPACKAGES.CLEANDOC := $(patsubst %,%.cleandoc, $(SUBPACKAGES))
SUBPACKAGES.CLEAN    := $(patsubst %,%.clean,    $(SUBPACKAGES))

.PHONY: $(SUBPACKAGES) $(SUBPACKAGES.INSTALL) $(SUBPACKAGES.CLEAN) $(SUBPACKAGES.DOC) $(SUBPACKAGES.RPM) $(SUBPACKAGES.CLEANRPM) $(SUBPACKAGES.CLEANDOC)

rpm: $(SUBPACKAGES) $(SUBPACKAGES.RPM)

doc: $(SUBPACKAGES.DOC)

cleanrpm: $(SUBPACKAGES.CLEANRPM)

clean: $(SUBPACKAGES.CLEAN)

cleandoc: $(SUBPACKAGES.CLEANDOC)

$(SUBPACKAGES):
	$(MAKE) -C $@

$(SUBPACKAGES.RPM):
	$(MAKE) -C $(patsubst %.rpm,%, $@) rpm

$(SUBPACKAGES.DOC):
	$(MAKE) -C $(patsubst %.doc,%, $@) html

$(SUBPACKAGES.CLEANRPM):
	$(MAKE) -C $(patsubst %.cleanrpm,%, $@) cleanrpm

$(SUBPACKAGES.CLEANDOC):
	$(MAKE) -C $(patsubst %.cleandoc,%, $@) cleandoc

$(SUBPACKAGES.CLEAN):
	$(MAKE) -C $(patsubst %.clean,%, $@) clean
