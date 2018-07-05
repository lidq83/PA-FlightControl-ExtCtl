all: mkbuild pa3extctl

mkbuild:
	@mkdir -p build

pa3extctl:
	@cd build && cmake ../ && make pa3extctl_output --silent
	
clean:
	@rm -rf build