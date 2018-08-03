ifndef PETA_STAGE
$(error "Error: PETA_STAGE environment variable not set.  Change to the root of your PetaLinux install, and source the settings.sh file")
endif
include ../apps.common.mk

LIB = memhub
APP = reg_stress_test

# Add any other object files to this list below
APP_OBJS = reg_stress_test.o
LIB_OBJS = memhub.o

all: build

build: $(APP)

$(LIB): $(LIB_OBJS)
	$(CXX) -std=c++11 $(CFLAGS) $(LDFLAGS) -shared -o lib$@.so $(LIB_OBJS) $(LDLIBS) -lmemsvc -pthread

$(APP): $(LIB) $(APP_OBJS)
	$(CXX) -std=c++11 $(CFLAGS) $(LDFLAGS) -o $@ $(APP_OBJS) $(LDLIBS) -lmemsvc -L./ -l$(LIB)

clean:
	-rm -f $(APP) *.elf *.gdb *.o *.so


%.o: %.cpp
	$(CXX) -std=c++0x -c $(CFLAGS) -o $@ $<

.PHONY: build
help:
	@echo ""
	@echo "Quick reference for various supported build targets for $(INSTANCE)."
	@echo "----------------------------------------------------"
	@echo "  clean                  clean out build objects"
	@echo "  all                    build $(INSTANCE)
	@echo "  build                  build subsystem"
