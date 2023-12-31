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
CMAKE_SOURCE_DIR = /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build

# Include any dependencies generated for this target.
include CMakeFiles/refresh.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/refresh.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/refresh.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/refresh.dir/flags.make

CMakeFiles/refresh.dir/refresh.cpp.o: CMakeFiles/refresh.dir/flags.make
CMakeFiles/refresh.dir/refresh.cpp.o: /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/refresh.cpp
CMakeFiles/refresh.dir/refresh.cpp.o: CMakeFiles/refresh.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/refresh.dir/refresh.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/refresh.dir/refresh.cpp.o -MF CMakeFiles/refresh.dir/refresh.cpp.o.d -o CMakeFiles/refresh.dir/refresh.cpp.o -c /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/refresh.cpp

CMakeFiles/refresh.dir/refresh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/refresh.dir/refresh.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/refresh.cpp > CMakeFiles/refresh.dir/refresh.cpp.i

CMakeFiles/refresh.dir/refresh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/refresh.dir/refresh.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/refresh.cpp -o CMakeFiles/refresh.dir/refresh.cpp.s

# Object files for target refresh
refresh_OBJECTS = \
"CMakeFiles/refresh.dir/refresh.cpp.o"

# External object files for target refresh
refresh_EXTERNAL_OBJECTS =

refresh: CMakeFiles/refresh.dir/refresh.cpp.o
refresh: CMakeFiles/refresh.dir/build.make
refresh: /usr/local/lib/libaws-cpp-sdk-s3.so
refresh: /usr/local/lib/libaws-cpp-sdk-core.so
refresh: /usr/local/lib/libaws-crt-cpp.a
refresh: /usr/local/lib/libaws-c-mqtt.a
refresh: /usr/local/lib/libaws-c-event-stream.a
refresh: /usr/local/lib/libaws-c-s3.a
refresh: /usr/local/lib/libaws-c-auth.a
refresh: /usr/local/lib/libaws-c-http.a
refresh: /usr/local/lib/libaws-c-io.a
refresh: /usr/local/lib/libs2n.a
refresh: /usr/local/lib/libcrypto.a
refresh: /usr/local/lib/libaws-c-compression.a
refresh: /usr/local/lib/libaws-c-cal.a
refresh: /usr/local/lib/libcrypto.so
refresh: /usr/local/lib/libaws-c-sdkutils.a
refresh: /usr/local/lib/libaws-checksums.a
refresh: /usr/local/lib/libaws-c-common.a
refresh: CMakeFiles/refresh.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable refresh"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/refresh.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/refresh.dir/build: refresh
.PHONY : CMakeFiles/refresh.dir/build

CMakeFiles/refresh.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/refresh.dir/cmake_clean.cmake
.PHONY : CMakeFiles/refresh.dir/clean

CMakeFiles/refresh.dir/depend:
	cd /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build /home/xxeniash/EPFL_internship/EPFL_internship/amazon/s3_exp/build/CMakeFiles/refresh.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/refresh.dir/depend

