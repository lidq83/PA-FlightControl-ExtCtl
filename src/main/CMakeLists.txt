add_executable(pa3extctl
	main.c
)

target_link_libraries(pa3extctl
	commander
	geo
	extctl
	uORB
	uorb_msgs
	${STD_LIBS}
)
