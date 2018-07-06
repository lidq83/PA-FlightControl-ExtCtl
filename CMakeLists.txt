#set(CMAKE_BUILD_TYPE
#	Debug
#)

set(CMAKE_CXX_FLAGS
	${CMAKE_CXX_FLAGS}
	-std=c11
)

set(STD_LIBS
	m
	pthread
)

include_directories(
	${PROJECT_BINARY_DIR}
	${PROJECT_SOURCE_DIR}/src
	${PROJECT_SOURCE_DIR}/src/main
	${PROJECT_SOURCE_DIR}/src/lib/geo
	${PROJECT_SOURCE_DIR}/src/lib/hrt
	${PROJECT_SOURCE_DIR}/src/modules/commander
	${PROJECT_SOURCE_DIR}/src/modules/navigator
	${PROJECT_SOURCE_DIR}/src/modules/extctl
	${PROJECT_SOURCE_DIR}/src/modules/uORB
)

add_subdirectory(msg)
add_subdirectory(src/main)
add_subdirectory(src/lib/geo)
add_subdirectory(src/lib/hrt)
add_subdirectory(src/modules/commander)
add_subdirectory(src/modules/navigator)
add_subdirectory(src/modules/extctl)
add_subdirectory(src/modules/uORB)

set(TARGET_FILE
	${PROJECT_BINARY_DIR}/src/main/pa3extctl
)

add_custom_target(pa3extctl_output DEPENDS ${TARGET_FILE})

add_custom_command(TARGET pa3extctl_output POST_BUILD
	COMMAND cp ${TARGET_FILE} ${PROJECT_BINARY_DIR}/
)

