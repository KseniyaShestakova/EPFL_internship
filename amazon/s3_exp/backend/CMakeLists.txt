cmake_minimum_required(VERSION 3.5)

project(libApp LANGUAGES C CXX)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_subdirectory(lib)
add_executable(app  main.c)
target_link_libraries(app backend)
add_definitions(${GLIB_CFLAGS_OTHER})
set_compiler_flags(app)
set_compiler_warnings(app)
target_link_libraries(app ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(app ${GLIB_LDFLAGS})
