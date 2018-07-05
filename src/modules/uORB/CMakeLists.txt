INCLUDE_DIRECTORIES(
	../../../src/modules/uORB
)

SET(SOURCE_FILES
	orb_manager.c
	topics/survey_information.cpp
)

ADD_LIBRARY(modules_uORB ${SOURCE_FILES})