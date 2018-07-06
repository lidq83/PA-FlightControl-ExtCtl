add_library(uORB
	SHARED
	orb_manager.c
)

target_link_libraries(uORB
	${STD_LIBS}
)
