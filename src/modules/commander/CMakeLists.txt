add_library(commander
	SHARED
	commander.c
)

target_link_libraries(commander
	${STD_LIBS}
)
