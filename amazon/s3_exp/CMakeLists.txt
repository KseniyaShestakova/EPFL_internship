
cmake_minimum_required(VERSION 3.3)
set(CMAKE_CXX_STANDARD 11)
project(app LANGUAGES CXX)

enable_testing()

find_package(PkgConfig REQUIRED)
pkg_search_module(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
set(BUILD_SHARED_LIBS ON CACHE STRING "Link to shared libraries by default.")

#Load required services/packages: This basic example uses S3.
find_package(AWSSDK REQUIRED COMPONENTS s3)
add_executable(${PROJECT_NAME} "test.cpp") #Add app's main starting file.
add_executable(setup "setup.cpp")
add_executable(finish "finish.cpp")
add_executable(refresh "refresh.cpp")

add_definitions(${GLIB_CFLAGS_OTHER})
set_compiler_flags(${PROJECT_NAME})
set_compiler_warnings(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(${PROJECT_NAME}  PRIVATE ${GLIB_LDFLAGS})

target_link_libraries(setup PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(setup  PRIVATE ${GLIB_LDFLAGS})

target_link_libraries(finish PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(finish  PRIVATE ${GLIB_LDFLAGS})

target_link_libraries(refresh PRIVATE ${AWSSDK_LINK_LIBRARIES})
target_link_libraries(refresh  PRIVATE ${GLIB_LDFLAGS})


include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
