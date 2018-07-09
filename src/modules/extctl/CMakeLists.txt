add_library(extctl
	SHARED
	extctl_cmd.c
	extctl_main.c
	extctl_pos.c
	extctl_protocol.c
	extctl_rc.c
	extctl_socket.c
	extctl_sp.c
	extctl_status.c
)

target_link_libraries(extctl
	${STD_LIBS}
)
