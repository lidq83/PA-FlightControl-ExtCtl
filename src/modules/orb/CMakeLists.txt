add_library(orb
	SHARED
	orb_manager.c
)

target_link_libraries(orb
	${STD_LIBS}
)
