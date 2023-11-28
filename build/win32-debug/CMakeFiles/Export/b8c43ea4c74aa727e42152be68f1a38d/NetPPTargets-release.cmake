#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libnetpp" for configuration "Release"
set_property(TARGET libnetpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libnetpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libnetpp.lib"
  )

list(APPEND _cmake_import_check_targets libnetpp )
list(APPEND _cmake_import_check_files_for_libnetpp "${_IMPORT_PREFIX}/lib/libnetpp.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
