# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = //oio-sds

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = //oio-sds

# Include any dependencies generated for this target.
include core/CMakeFiles/tool_roundtrip.dir/depend.make

# Include the progress variables for this target.
include core/CMakeFiles/tool_roundtrip.dir/progress.make

# Include the compile flags for this target's objects.
include core/CMakeFiles/tool_roundtrip.dir/flags.make

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o: core/CMakeFiles/tool_roundtrip.dir/flags.make
core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o: core/tool_roundtrip.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=//oio-sds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o"
	cd //oio-sds/core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o   -c //oio-sds/core/tool_roundtrip.c

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.i"
	cd //oio-sds/core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E //oio-sds/core/tool_roundtrip.c > CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.i

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.s"
	cd //oio-sds/core && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S //oio-sds/core/tool_roundtrip.c -o CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.s

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.requires:

.PHONY : core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.requires

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.provides: core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.requires
	$(MAKE) -f core/CMakeFiles/tool_roundtrip.dir/build.make core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.provides.build
.PHONY : core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.provides

core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.provides.build: core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o


# Object files for target tool_roundtrip
tool_roundtrip_OBJECTS = \
"CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o"

# External object files for target tool_roundtrip
tool_roundtrip_EXTERNAL_OBJECTS =

core/tool_roundtrip: core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o
core/tool_roundtrip: core/CMakeFiles/tool_roundtrip.dir/build.make
core/tool_roundtrip: core/liboiosds.so.0.0.0
core/tool_roundtrip: core/liboiocore.so.0.0.0
core/tool_roundtrip: /usr/lib/x86_64-linux-gnu/libcurl.so
core/tool_roundtrip: core/CMakeFiles/tool_roundtrip.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=//oio-sds/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable tool_roundtrip"
	cd //oio-sds/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tool_roundtrip.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
core/CMakeFiles/tool_roundtrip.dir/build: core/tool_roundtrip

.PHONY : core/CMakeFiles/tool_roundtrip.dir/build

core/CMakeFiles/tool_roundtrip.dir/requires: core/CMakeFiles/tool_roundtrip.dir/tool_roundtrip.c.o.requires

.PHONY : core/CMakeFiles/tool_roundtrip.dir/requires

core/CMakeFiles/tool_roundtrip.dir/clean:
	cd //oio-sds/core && $(CMAKE_COMMAND) -P CMakeFiles/tool_roundtrip.dir/cmake_clean.cmake
.PHONY : core/CMakeFiles/tool_roundtrip.dir/clean

core/CMakeFiles/tool_roundtrip.dir/depend:
	cd //oio-sds && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" //oio-sds //oio-sds/core //oio-sds //oio-sds/core //oio-sds/core/CMakeFiles/tool_roundtrip.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/CMakeFiles/tool_roundtrip.dir/depend

