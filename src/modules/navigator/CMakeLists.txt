add_library(navigator
	SHARED
	navigator.c
)

target_link_libraries(navigator
	${STD_LIBS}
)
