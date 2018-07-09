add_library(commander
	SHARED
	commander.c
	cmd_status_machine.c
)

target_link_libraries(commander
	${STD_LIBS}
)
