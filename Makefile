all: mkbuild uorb_msg pa3extctl

mkbuild:
	@mkdir -p build
	@mkdir -p build/uORB
	@mkdir -p build/msg

uorb_msg:
	@cp src/modules/uORB/uORB.h build/uORB
	@cp src/modules/uORB/uORBTopics.h build/uORB
	@cd build/msg && cmake ../../msg && make uorb_headers && make uorb_sources
	@cp -rf build/msg/uORB build/

pa3extctl:
	@cd build && cmake ../ && make pa3extctl_output --silent
	
clean:
	@rm -rf build