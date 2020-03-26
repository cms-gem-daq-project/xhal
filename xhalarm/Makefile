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

XHAL_VER_MAJOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[1];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_MINOR:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[2];}' | awk '{split($$0,b,":"); print b[2];}')
XHAL_VER_PATCH:=$(shell $(BUILD_HOME)/$(Project)/config/tag2rel.sh | awk '{split($$0,a," "); print a[3];}' | awk '{split($$0,b,":"); print b[2];}')

INSTALL_PREFIX=/mnt/persistent/xhal

include $(BUILD_HOME)/$(Project)/config/mfCommonDefs.mk
include $(BUILD_HOME)/$(Project)/config/mfZynq.mk
include $(BUILD_HOME)/$(Project)/config/mfRPMRules.mk

ADDFLAGS=-std=gnu++14

IncludeDirs  = ${BUILD_HOME}/${Project}/xhalcore/include
INC=$(IncludeDirs:%=-I%)

Libraries+= -llog4cplus -lxerces-c -lstdc++
LIB=$(LibraryDirs)
LIB+= $(Libraries)

LDFLAGS= -shared
SRCS_XHAL = $(shell echo ../xhalcore/src/common/utils/*.cpp)
OBJS_XHAL = $(SRCS_XHAL:.cpp=.o)

XHAL_LIB=${BUILD_HOME}/${Project}/${LongPackage}/lib/libxhal.so

.PHONY: clean rpc prerpm

default: clean
	@echo "Running default target"
	$(MakeDir) $(PackageDir)

_rpmprep: preprpm
	@echo "Running _rpmprep target"
preprpm: default
	@echo "Running preprpm target"
	@cp -rf lib $(PackageDir)

build:${XHAL_LIB}

_all: clean ${XHAL_LIB}

$(XHAL_LIB): $(OBJS_XHAL)
	@mkdir -p ${BUILD_HOME}/${Project}/${LongPackage}/lib
	$(CC) $(CFLAGS) $(ADDFLAGS) ${LDFLAGS} $(INC) $(LIB) -o $@ $^

$(OBJS_XHAL):$(SRCS_XHAL)
	$(CC) $(CFLAGS) $(ADDFLAGS) $(INC) $(LIB) -c -o $@ $<

%.o: %.c
	$(CC) -std=gnu99 -c $(CFLAGS) -o $@ $<
%.o: %.cc
	$(CXX) -std=c++0x -c $(CFLAGS) -o $@ $<

clean: cleanrpm
	-${RM} ${XHAL_LIB} ${OBJS_XHAL}
	-rm -rf $(PackageDir)

doc:
	@echo "TO DO"

cleandoc:
	@echo "TO DO"
