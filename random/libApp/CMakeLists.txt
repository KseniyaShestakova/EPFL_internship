cmake_minimum_required(VERSION 3.5)

project(libApp LANGUAGES C CXX)
add_subdirectory(foo)
add_executable(app  main.c)
target_link_libraries(app PRIVATE foo)
