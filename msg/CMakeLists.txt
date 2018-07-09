set(msg_files
	ext_cmd.msg
	ext_rc.msg
	ext_sys_status.msg
	ext_vehicle_pos.msg
	ext_vehicle_sp.msg
	main_state.msg
	nav_state.msg
)

# headers
set(msg_out_path ${PROJECT_BINARY_DIR}/uORB/topics)
set(msg_source_out_path	${CMAKE_CURRENT_BINARY_DIR}/topics_sources)

set(uorb_headers)
foreach(msg_file ${msg_files})
	get_filename_component(msg ${msg_file} NAME_WE)
	list(APPEND uorb_headers ${msg_out_path}/${msg}.h)
	list(APPEND uorb_sources ${msg_source_out_path}/${msg}.c)
endforeach()

# Generate uORB headers
add_custom_command(OUTPUT ${uorb_headers}
	COMMAND ${PYTHON_EXECUTABLE} tools/px_generate_uorb_topic_files.py
		--headers
		-f ${msg_files}
		-i ${CMAKE_CURRENT_SOURCE_DIR}
		-o ${msg_out_path}
		-e templates/uorb
		-t ${CMAKE_CURRENT_BINARY_DIR}/tmp/headers
		-q
	DEPENDS ${msg_files}
	COMMENT "Generating uORB topic headers"
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	VERBATIM
	)
add_custom_target(uorb_headers DEPENDS ${uorb_headers})

# Generate uORB sources
add_custom_command(OUTPUT ${uorb_sources}
	COMMAND ${PYTHON_EXECUTABLE} tools/px_generate_uorb_topic_files.py
		--sources
		-f ${msg_files}
		-i ${CMAKE_CURRENT_SOURCE_DIR}
		-o ${msg_source_out_path}
		-e templates/uorb
		-t ${CMAKE_CURRENT_BINARY_DIR}/tmp/sources
		-q
	DEPENDS ${msg_files}
	COMMENT "Generating uORB topic sources"
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	VERBATIM
	)
add_custom_target(uorb_sources DEPENDS ${uorb_sources})

add_library(uorb_msgs ${uorb_sources})
add_dependencies(uorb_msgs uorb_headers)
