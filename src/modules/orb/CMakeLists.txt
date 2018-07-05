add_library(orb
	SHARED
	orb_manager.c
	uORB/topics/survey_information.cpp
)

target_link_libraries(orb
	${STD_LIBS}
)
