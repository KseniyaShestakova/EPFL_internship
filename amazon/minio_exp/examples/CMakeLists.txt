SET(S3_LIBS ${requiredlibs})

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

ADD_EXECUTABLE(TestAll TestAll.cc)
TARGET_LINK_LIBRARIES(TestAll PRIVATE miniocpp ${S3_LIBS})

ADD_EXECUTABLE(test test.cpp)
TARGET_LINK_LIBRARIES(test PRIVATE miniocpp ${S3_LIBS})
target_link_libraries(test PRIVATE GTest::GTest)

ADD_EXECUTABLE(setup setup.cpp)
TARGET_LINK_LIBRARIES(setup PRIVATE miniocpp ${S3_LIBS})

ADD_EXECUTABLE(finish finish.cpp)
TARGET_LINK_LIBRARIES(finish PRIVATE miniocpp ${S3_LIBS})

include(GoogleTest)
gtest_discover_tests(test)
