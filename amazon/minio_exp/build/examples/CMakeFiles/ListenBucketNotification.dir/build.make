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
include examples/CMakeFiles/ListenBucketNotification.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/ListenBucketNotification.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/ListenBucketNotification.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/ListenBucketNotification.dir/flags.make

examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o: examples/CMakeFiles/ListenBucketNotification.dir/flags.make
examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o: /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/ListenBucketNotification.cc
examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o: examples/CMakeFiles/ListenBucketNotification.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o -MF CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o.d -o CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o -c /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/ListenBucketNotification.cc

examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.i"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/ListenBucketNotification.cc > CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.i

examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.s"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/ListenBucketNotification.cc -o CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.s

# Object files for target ListenBucketNotification
ListenBucketNotification_OBJECTS = \
"CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o"

# External object files for target ListenBucketNotification
ListenBucketNotification_EXTERNAL_OBJECTS =

examples/ListenBucketNotification: examples/CMakeFiles/ListenBucketNotification.dir/ListenBucketNotification.cc.o
examples/ListenBucketNotification: examples/CMakeFiles/ListenBucketNotification.dir/build.make
examples/ListenBucketNotification: src/libminiocpp.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurlpp.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libinih.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libz.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libpugixml.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/ListenBucketNotification: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/ListenBucketNotification: examples/CMakeFiles/ListenBucketNotification.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ListenBucketNotification"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ListenBucketNotification.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/ListenBucketNotification.dir/build: examples/ListenBucketNotification
.PHONY : examples/CMakeFiles/ListenBucketNotification.dir/build

examples/CMakeFiles/ListenBucketNotification.dir/clean:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/ListenBucketNotification.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/ListenBucketNotification.dir/clean

examples/CMakeFiles/ListenBucketNotification.dir/depend:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xxeniash/EPFL_internship/minio_dev/minio-cpp /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples/CMakeFiles/ListenBucketNotification.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/ListenBucketNotification.dir/depend
