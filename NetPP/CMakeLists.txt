add_library(libnetpp STATIC  
    ${NETPP_INCLUDE_DIRS}/netpp/network.hpp
    ${NETPP_INCLUDE_DIRS}/netpp/Log.hpp
    ${NETPP_INCLUDE_DIRS}/netpp/Error.hpp
    ${NETPP_INCLUDE_DIRS}/netpp/SockAddress.hpp
    ${NETPP_INCLUDE_DIRS}/netpp/Socket.hpp
    Error.cpp
    SockAddress.cpp
    Socket.cpp
)

target_include_directories(libnetpp
    INTERFACE
	PUBLIC $<BUILD_INTERFACE:${NETPP_INCLUDE_DIRS}>
    PUBLIC $<INSTALL_INTERFACE:include>
)

if(NETPP_PLATFORM_WINDOWS)
    target_link_libraries(libnetpp PUBLIC ws2_32)
endif()
