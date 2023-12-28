find_path(NetPP_INCLUDE_DIR
	NAMES netpp/Socket.hpp
    PATHS $ENV{ProgramFiles\(x86\)}/NetPP/include
    PATH_SUFFIXES netpp
)

if(NetPP_INCLUDE_DIR)
 message(STATUS "Found NetPP include dir: ${NetPP_INCLUDE_DIR}")
endif()

find_library(NetPP_LIBRARY
    NAMES libnetpp.a libnetpp.lib
    PATHS $ENV{ProgramFiles\(x86\)}/NetPP/lib
)

if(NetPP_LIBRARY)
 message(STATUS "Found NetPP library: ${NetPP_LIBRARY}")
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NetPP
    REQUIRED_VARS NetPP_INCLUDE_DIR NetPP_LIBRARY
    VERSION_VAR NetPP_VERSION
)