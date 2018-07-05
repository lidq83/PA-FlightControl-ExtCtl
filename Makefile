all: mkbuild pa3extctl

mkbuild:
	mkdir -p build

pa3extctl:
	cd build && cmake ../ && make && make pa3extctl_output
	
clean:
	rm -rvf build