INCLUDE_DIRECTORIES(
	../../../src
)

SET(SOURCE_FILES
	commander.c
)

ADD_LIBRARY(modules_commander ${SOURCE_FILES})