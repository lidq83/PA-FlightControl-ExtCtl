add_library(hrt
	SHARED
	hrt.c
)

target_link_libraries (hrt
	${STD_LIBS}
)
