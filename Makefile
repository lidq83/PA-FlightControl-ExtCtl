RPI_DIR = pi@192.168.43.9:work/extctl

NINJA_BUILD := $(shell ninja --version 2>/dev/null)
ifdef NINJA_BUILD
    PA_CMAKE_GENERATOR ?= "Ninja"
    PA_MAKE = ninja
    SILENT =
else
	PA_CMAKE_GENERATOR ?= "Unix Makefiles"
    PA_MAKE = make
    SILENT = --silent
    PA_MAKE_ARGS = -j$(j) --no-print-directory
endif

all: mkbuild uorb_msg pa3extctl

rpi: mkbuild uorb_msg uorb_msg_rpi pa3rpi_extctl

mkbuild:
	@if [ ! -e $(PWD)/build/CMakeCache.txt ]; then mkdir -p $(PWD)/build; fi
	@if [ ! -e $(PWD)/build/uORB/uORB.h ]; then mkdir -p build/uORB  && mkdir -p build/msg && cp src/modules/uORB/uORB.h build/uORB  && cp src/modules/uORB/uORBTopics.h build/uORB;fi

uorb_msg:
	@if [ ! -e $(PWD)/build/uORB/topics/ext_cmd.h ]; then cd build/msg && cmake  ../../msg -G$(PA_CMAKE_GENERATOR) && ${PA_MAKE} uorb_headers && $(PA_MAKE) uorb_sources; fi
	@if [ ! -e $(PWD)/build/uORB/topics/ext_cmd.h ]; then cp -rf build/msg/uORB build/; fi
	
uorb_msg_rpi:
	@cd build/msg && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../../msg  -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) uorb_headers && $(PA_MAKE) uorb_sources
	
pa3extctl:
	@cd build && cmake ../ -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) pa3extctl_output ${SILENT}

pa3rpi_extctl:
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../ -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) pa3extctl_output ${SILENT}

rpi_install:
	@./Tools/rpi_install.sh

clean:
	@rm -rf build
