add_executable(pa3extctl
	main.c
)

target_link_libraries(pa3extctl
	geo
	hrt
	param
	airline
	commander
	navigator
	extctl
	uORB
	uorb_msgs
	${STD_LIBS}
)
