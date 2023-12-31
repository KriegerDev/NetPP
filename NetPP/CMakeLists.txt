add_library(libnetpp STATIC  
    ${NETPP_INCLUDE_DIRS}/netpp/network.hpp
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
    target_link_libraries(libnetpp 
    PUBLIC ws2_32
)
endif()

install(DIRECTORY ${NETPP_INCLUDE_DIRS}/netpp DESTINATION include)
install(TARGETS libnetpp
	EXPORT NetPPTargets
    DESTINATION cmake
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)
install(EXPORT NetPPTargets
  FILE NetPPTargets.cmake
  NAMESPACE NetPP::
  DESTINATION cmake/NetPP
)