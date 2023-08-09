SET(S3_LIBS ${requiredlibs})

ADD_EXECUTABLE(TestAll TestAll.cc)
TARGET_LINK_LIBRARIES(TestAll miniocpp ${S3_LIBS})

ADD_EXECUTABLE(Backend Backend.cc)
TARGET_LINK_LIBRARIES(Backend miniocpp ${S3_LIBS})
