add_library(geo
	SHARED
	geo.c
)

target_link_libraries (geo
	${STD_LIBS}
)
