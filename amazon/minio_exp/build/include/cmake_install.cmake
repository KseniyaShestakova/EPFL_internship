# Install script for directory: /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/miniocpp" TYPE FILE FILES
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/args.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/baseclient.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/client.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/config.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/credentials.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/error.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/http.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/providers.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/request.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/response.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/select.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/signer.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/sse.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/types.h"
    "/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/include/utils.h"
    )
endif()

