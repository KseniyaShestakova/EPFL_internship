#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::inih::inih" for configuration "Debug"
set_property(TARGET unofficial::inih::inih APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(unofficial::inih::inih PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "C;CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/libinih.a"
  )

list(APPEND _cmake_import_check_targets unofficial::inih::inih )
list(APPEND _cmake_import_check_files_for_unofficial::inih::inih "${_IMPORT_PREFIX}/debug/lib/libinih.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
