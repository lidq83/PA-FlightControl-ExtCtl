RPI_DIR = pi@192.168.43.9:work/extctl

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
	@cd build/msg && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-native.cmake ../../msg && make uorb_headers && make uorb_sources
	@cp -rf build/msg/uORB build/
	
uorb_msg_rpi:
	@cp src/modules/uORB/uORB.h build/uORB
	@cp src/modules/uORB/uORBTopics.h build/uORB
	@cd build/msg && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../../msg && make uorb_headers && make uorb_sources
	@cp -rf build/msg/uORB build/

pa3extctl:
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-native.cmake ../ && make pa3extctl_output --silent

pa3rpi_extctl:
	@cd build && cmake -DCMAKE_TOOLCHAIN_FILE=../toolchains/Toolchain-arm-linux-gnueabihf.cmake ../ && make pa3extctl_output --silent

rpi_install:
	@./Tools/rpi_install.sh

clean:
	@rm -rf build