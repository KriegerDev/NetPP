add_executable(udp_server
	udp_server.cpp
)

target_link_libraries(udp_server
	${NetPP_LIBRARY}
	ws2_32
)

target_include_directories(udp_server
	PRIVATE
		${NetPP_INCLUDE_DIR}
)