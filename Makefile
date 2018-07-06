all: mkbuild mkmsg pa3extctl

mkbuild:
	@mkdir -p build
	@mkdir -p build/msg
	
mkmsg:
	@cp src/modules/orb/uORB/uORB.h build/msg
	@cp src/modules/orb/uORB/uORBTopics.h build/msg

pa3extctl:
	@cd build && cmake ../ && make pa3extctl_output --silent
	
clean:
	@rm -rf build