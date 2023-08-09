#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "unofficial::inih::inih" for configuration "Release"
set_property(TARGET unofficial::inih::inih APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(unofficial::inih::inih PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libinih.a"
  )

list(APPEND _cmake_import_check_targets unofficial::inih::inih )
list(APPEND _cmake_import_check_files_for_unofficial::inih::inih "${_IMPORT_PREFIX}/lib/libinih.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
