# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/xxeniash/.local/lib/python3.9/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/xxeniash/.local/lib/python3.9/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/xxeniash/EPFL_internship/minio_dev/minio-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/GetBucketNotification.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/GetBucketNotification.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/GetBucketNotification.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/GetBucketNotification.dir/flags.make

examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o: examples/CMakeFiles/GetBucketNotification.dir/flags.make
examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o: /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/GetBucketNotification.cc
examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o: examples/CMakeFiles/GetBucketNotification.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o -MF CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o.d -o CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o -c /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/GetBucketNotification.cc

examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.i"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/GetBucketNotification.cc > CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.i

examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.s"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/GetBucketNotification.cc -o CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.s

# Object files for target GetBucketNotification
GetBucketNotification_OBJECTS = \
"CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o"

# External object files for target GetBucketNotification
GetBucketNotification_EXTERNAL_OBJECTS =

examples/GetBucketNotification: examples/CMakeFiles/GetBucketNotification.dir/GetBucketNotification.cc.o
examples/GetBucketNotification: examples/CMakeFiles/GetBucketNotification.dir/build.make
examples/GetBucketNotification: src/libminiocpp.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurlpp.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libinih.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libz.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libpugixml.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/GetBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/GetBucketNotification: examples/CMakeFiles/GetBucketNotification.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable GetBucketNotification"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/GetBucketNotification.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/GetBucketNotification.dir/build: examples/GetBucketNotification
.PHONY : examples/CMakeFiles/GetBucketNotification.dir/build

examples/CMakeFiles/GetBucketNotification.dir/clean:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/GetBucketNotification.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/GetBucketNotification.dir/clean

examples/CMakeFiles/GetBucketNotification.dir/depend:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xxeniash/EPFL_internship/minio_dev/minio-cpp /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples/CMakeFiles/GetBucketNotification.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/GetBucketNotification.dir/depend

