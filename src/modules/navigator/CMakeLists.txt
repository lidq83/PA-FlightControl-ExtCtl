add_library(navigator
	SHARED
	navigator.c
	nav_status_machine.c
	nav_block_reached.c
	nav_block_init.c
	nav_block_takeoff.c
	nav_block_mission.c
	nav_block_loiter.c
	nav_block_rtl.c
	nav_block_failoff.c
	nav_block_failsafe.c
)

target_link_libraries(navigator
	${STD_LIBS}
)
