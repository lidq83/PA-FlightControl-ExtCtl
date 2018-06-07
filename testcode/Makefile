all:
	mkdir -p build
	gcc -g -std=gnu11 -lm -lpthread -o ./build/extctl extctl_main.c \
		extctl_sp.c	\
		extctl_pos.c	\
		extctl_rc.c	\
		extctl_cmd.c	\
		extctl_land.c

clean:
	rm -rvf build/extctl
