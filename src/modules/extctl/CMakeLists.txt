INCLUDE_DIRECTORIES(
	../../../src
)

SET(SOURCE_FILES
	extctl_main.c
	example_airline.c
	extctl_airline.c
	extctl_cmd.c
	extctl_pos.c
	extctl_protocol.c
	extctl_rc.c
	extctl_socket.c
	extctl_sp.c
	extctl_status.c
)

ADD_LIBRARY(modules_extctl ${SOURCE_FILES})