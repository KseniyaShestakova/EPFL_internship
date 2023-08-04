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
CMAKE_SOURCE_DIR = /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld

# Include any dependencies generated for this target.
include lib/CMakeFiles/backend.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lib/CMakeFiles/backend.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/backend.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/backend.dir/flags.make

lib/CMakeFiles/backend.dir/backend.cpp.o: lib/CMakeFiles/backend.dir/flags.make
lib/CMakeFiles/backend.dir/backend.cpp.o: /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/lib/backend.cpp
lib/CMakeFiles/backend.dir/backend.cpp.o: lib/CMakeFiles/backend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/backend.dir/backend.cpp.o"
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lib/CMakeFiles/backend.dir/backend.cpp.o -MF CMakeFiles/backend.dir/backend.cpp.o.d -o CMakeFiles/backend.dir/backend.cpp.o -c /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/lib/backend.cpp

lib/CMakeFiles/backend.dir/backend.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/backend.dir/backend.cpp.i"
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/lib/backend.cpp > CMakeFiles/backend.dir/backend.cpp.i

lib/CMakeFiles/backend.dir/backend.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/backend.dir/backend.cpp.s"
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/lib/backend.cpp -o CMakeFiles/backend.dir/backend.cpp.s

# Object files for target backend
backend_OBJECTS = \
"CMakeFiles/backend.dir/backend.cpp.o"

# External object files for target backend
backend_EXTERNAL_OBJECTS =

lib/libbackend.so: lib/CMakeFiles/backend.dir/backend.cpp.o
lib/libbackend.so: lib/CMakeFiles/backend.dir/build.make
lib/libbackend.so: /usr/local/lib/libaws-cpp-sdk-s3.so
lib/libbackend.so: /usr/local/lib/libaws-cpp-sdk-core.so
lib/libbackend.so: /usr/local/lib/libaws-crt-cpp.a
lib/libbackend.so: /usr/local/lib/libaws-c-mqtt.a
lib/libbackend.so: /usr/local/lib/libaws-c-event-stream.a
lib/libbackend.so: /usr/local/lib/libaws-c-s3.a
lib/libbackend.so: /usr/local/lib/libaws-c-auth.a
lib/libbackend.so: /usr/local/lib/libaws-c-http.a
lib/libbackend.so: /usr/local/lib/libaws-c-io.a
lib/libbackend.so: /usr/local/lib/libs2n.a
lib/libbackend.so: /usr/local/lib/libcrypto.a
lib/libbackend.so: /usr/local/lib/libaws-c-compression.a
lib/libbackend.so: /usr/local/lib/libaws-c-cal.a
lib/libbackend.so: /usr/local/lib/libcrypto.so
lib/libbackend.so: /usr/local/lib/libaws-c-sdkutils.a
lib/libbackend.so: /usr/local/lib/libaws-checksums.a
lib/libbackend.so: /usr/local/lib/libaws-c-common.a
lib/libbackend.so: lib/CMakeFiles/backend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libbackend.so"
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/backend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/backend.dir/build: lib/libbackend.so
.PHONY : lib/CMakeFiles/backend.dir/build

lib/CMakeFiles/backend.dir/clean:
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib && $(CMAKE_COMMAND) -P CMakeFiles/backend.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/backend.dir/clean

lib/CMakeFiles/backend.dir/depend:
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/lib /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/backend/bld/lib/CMakeFiles/backend.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/backend.dir/depend

