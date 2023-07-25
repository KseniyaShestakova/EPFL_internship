SET(S3_LIBS ${requiredlibs})

ADD_EXECUTABLE(TestAll TestAll.cc)
TARGET_LINK_LIBRARIES(TestAll miniocpp ${S3_LIBS})

