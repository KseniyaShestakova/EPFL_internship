find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")

find_package(AWSSDK REQUIRED COMPONENTS s3)
add_library(backend backend.cpp backend.h)

add_definitions(${GLIB_CFLAGS_OTHER})
set_compiler_flags(backend)
set_compiler_warnings(backend)
target_link_libraries(backend ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(backend ${GLIB_LDFLAGS})
