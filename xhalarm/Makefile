BUILD_HOME   := $(shell dirname `cd ../; pwd`)
Project      := xhal
Package      := xhal
ShortPackage := xhal
LongPackage  := xhalarm
PackageName  := $(ShortPackage)
PackagePath  := $(shell pwd)
PackageDir   := pkg/$(ShortPackage)
Packager     := Mykhailo Dalchenko
Arch         := arm

ProjectBase = $(BUILD_HOME)/$(Project)
ConfigDir   = $(ProjectBase)/config
PackageBase = $(shell pwd)

include $(ConfigDir)/mfCommonDefs.mk
include $(ConfigDir)/mfZynq.mk
include $(ConfigDir)/mfRPMRules.mk

PackageSourceDir     = $(ProjectBase)/xhalcore/src/common
PackageTestSourceDir = $(PackageBase)/test
PackageIncludeDir    = $(ProjectBase)/xhalcore/include
PackageLibraryDir    = $(PackageBase)/lib
PackageExecDir       = $(PackageBase)/bin
PackageObjectDir     = $(PackageBase)/src/linux/$(Arch)

XHAL_VER_MAJOR:=$(shell $(ConfigDir)/tag2rel.sh | awk '{split($$0,a," "); print a[1];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_MINOR:=$(shell $(ConfigDir)/tag2rel.sh | awk '{split($$0,a," "); print a[2];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_PATCH:=$(shell $(ConfigDir)/tag2rel.sh | awk '{split($$0,a," "); print a[3];}' | awk '{split($$0,b,":"); print b[2];}')

ADDFLAGS=-std=gnu++14

IncludeDirs+= $(PackageIncludeDir)
INC=$(IncludeDirs:%=-I%)

Libraries+=-llog4cplus -lxerces-c -lstdc++

LDFLAGS+=-shared $(LibraryDirs)

SRCS_XHAL = $(shell echo $(PackageSourceDir)/utils/*.cpp)

AUTODEPS_XHAL = $(patsubst $(PackageSourceDir)/%.cpp,$(PackageObjectDir)/%.d,$(SRCS_XHAL))

OBJS_XHAL = $(patsubst %.d,%.o,$(AUTODEPS_XHAL))

XHAL_LIB = $(PackageLibraryDir)/libxhal.so

TargetLibraries:= xhal

# destination path macro we'll use below
df = $(PackageObjectDir)/$(*F)

.PHONY: clean cleanall prerpm

default: build
	@echo "Running default target"
	$(MakeDir) $(PackageDir)

_rpmprep: preprpm
	@echo "Running _rpmprep target"

preprpm: default
	@echo "Running preprpm target"
	@cp -rf lib $(PackageDir)

_all: build

xhal: $(XHAL_LIB)

doc:
	@echo "TO DO"

## adapted from http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
## Generic object creation rule, generate dependencies and use them later
$(PackageObjectDir)/%.o: $(PackageSourceDir)/%.cpp
	$(MakeDir) $(@D)
	$(CC) $(CFLAGS) $(ADDFLAGS) $(INC) -c -MT $@ -MMD -MP -MF $(@D)/$(*F).Td -o $@ $<
	mv $(@D)/$(*F).Td $(@D)/$(*F).d
	touch $@

## dummy rule for dependencies
$(PackageObjectDir)/%.d:

## mark dependencies and objects as not auto-removed
.PRECIOUS: $(PackageObjectDir)/%.d
.PRECIOUS: $(PackageObjectDir)/%.o

## Force rule for all target library names
$(TargetLibraries):

$(XHAL_LIB): $(OBJS_XHAL) 
	$(MakeDir) -p $(@D)
	$(CC) $(ADDFLAGS) $(LDFLAGS) -shared -Wl,-soname,$(@F) -o $@ $^ $(Libraries)

## FIXME obsolete? only for xcompiled things?
# %.o: %.c
# 	$(CC) -std=gnu99 -c $(CFLAGS) -o $@ $<
# %.o: %.cc
# 	$(CXX) -std=c++0x -c $(CFLAGS) -o $@ $<

build: $(TargetLibraries)

clean:
	-rm -rf $(OBJS_XHAL)
	-rm -rf $(PackageLibraryDir)
	-rm -rf $(PackageExecDir)
	-rm -rf $(PackageDir)

cleandoc: 
	@echo "TO DO"

cleanall: clean cleandoc
	-rm -rf $(PackageObjectDir)
