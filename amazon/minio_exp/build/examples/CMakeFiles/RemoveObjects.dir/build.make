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
include examples/CMakeFiles/RemoveObjects.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include examples/CMakeFiles/RemoveObjects.dir/compiler_depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/RemoveObjects.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/RemoveObjects.dir/flags.make

examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o: examples/CMakeFiles/RemoveObjects.dir/flags.make
examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o: /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/RemoveObjects.cc
examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o: examples/CMakeFiles/RemoveObjects.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o -MF CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o.d -o CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o -c /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/RemoveObjects.cc

examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.i"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/RemoveObjects.cc > CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.i

examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.s"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples/RemoveObjects.cc -o CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.s

# Object files for target RemoveObjects
RemoveObjects_OBJECTS = \
"CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o"

# External object files for target RemoveObjects
RemoveObjects_EXTERNAL_OBJECTS =

examples/RemoveObjects: examples/CMakeFiles/RemoveObjects.dir/RemoveObjects.cc.o
examples/RemoveObjects: examples/CMakeFiles/RemoveObjects.dir/build.make
examples/RemoveObjects: src/libminiocpp.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libcurlpp.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libinih.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libcurl-d.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libz.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libpugixml.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libssl.a
examples/RemoveObjects: vcpkg_installed/x64-linux/debug/lib/libcrypto.a
examples/RemoveObjects: examples/CMakeFiles/RemoveObjects.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RemoveObjects"
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RemoveObjects.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/RemoveObjects.dir/build: examples/RemoveObjects
.PHONY : examples/CMakeFiles/RemoveObjects.dir/build

examples/CMakeFiles/RemoveObjects.dir/clean:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/RemoveObjects.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/RemoveObjects.dir/clean

examples/CMakeFiles/RemoveObjects.dir/depend:
	cd /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xxeniash/EPFL_internship/minio_dev/minio-cpp /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples /home/xxeniash/EPFL_internship/minio_dev/minio-cpp/build/examples/CMakeFiles/RemoveObjects.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/RemoveObjects.dir/depend
