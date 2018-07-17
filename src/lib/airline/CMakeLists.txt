add_library(airline
	SHARED
	airline.c
)

target_link_libraries (airline
	${STD_LIBS}
)
