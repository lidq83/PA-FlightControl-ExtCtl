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

rpi: mkbuild uorb_msg_rpi pa3rpi_extctl

mkbuild:
	@mkdir -p build
	@mkdir -p build/uORB
	@mkdir -p build/msg
	@mkdir -p build/rpi/lib
	@mkdir -p build/rpi/uORB

uorb_msg:
	@cp src/modules/uORB/uORB.h build/uORB
	@cp src/modules/uORB/uORBTopics.h build/uORB
	@cd build/msg && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-native.cmake ../../msg -G$(PA_CMAKE_GENERATOR) && ${PA_MAKE} uorb_headers && $(PA_MAKE) uorb_sources
	@cp -rf build/msg/uORB build/
	
uorb_msg_rpi:
	@cp src/modules/uORB/uORB.h build/uORB
	@cp src/modules/uORB/uORBTopics.h build/uORB
	@cd build/msg && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../../msg  -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) uorb_headers && $(PA_MAKE) uorb_sources
	@cp -rf build/msg/uORB build/

pa3extctl:
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-native.cmake ../ -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) pa3extctl_output ${SILENT}

pa3rpi_extctl:
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../ -G$(PA_CMAKE_GENERATOR) && $(PA_MAKE) pa3extctl_output ${SILENT}

rpi_install:
	@./Tools/rpi_install.sh

clean:
	@rm -rf build
