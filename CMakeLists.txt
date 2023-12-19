cmake_minimum_required(VERSION 3.8)
project(NetPP)

set(NETPP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(NETPP_CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

list(APPEND CMAKE_MODULE_PATH ${NETPP_CMAKE_MODULE_PATH})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    message("Compiling with Debug option")
endif()

# Exemplo de configuração para compilação em modo Release
if(CMAKE_BUILD_TYPE MATCHES Release)
    message("Compiling in Release mode")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(NETPP_PLATFORM_WINDOWS TRUE)
    message("Detected Windows platform")
    add_compile_definitions(NETPP_PLATFORM_WINDOWS)
elseif(UNIX AND NOT APPLE)
    set(NETPP_PLATFORM_LINUX TRUE)
    message("Detected Linux platform")
    add_compile_definitions(NETPP_PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()

option(NETPP_CUSTOM_INSTALL_DIR "Custom install dir" OFF)
option(NETPP_TESTS_OPT "Build tests" OFF)


if(NETPP_CUSTOM_INSTALL_DIR)
	set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)
	message(STATUS "Custom install dir enabled")
endif()

add_subdirectory(NetPP)

if(NETPP_TESTS_OPT)
    add_subdirectory(tests)
    message(STATUS "Tests enabled")
endif()

include(CMakePackageConfigHelpers)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/NetPPConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/NetPPConfig.cmake"
  INSTALL_DESTINATION "cmake/NetPP"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/NetPPConfigVersion.cmake"
  VERSION "${NetPP_VERSION_MAJOR}.${NetPP_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/NetPPConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/cmake/NetPPConfigVersion.cmake
  DESTINATION cmake/NetPP
)
export(EXPORT NetPPTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/NetPPTargets.cmake"
)
