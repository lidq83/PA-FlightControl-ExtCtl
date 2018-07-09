add_library(commander
	SHARED
	commander.c
	status_machine.c
)

target_link_libraries(commander
	${STD_LIBS}
)
