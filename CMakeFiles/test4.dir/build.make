# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /usr/local/cmake-3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/local/cmake-3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/travis/build/Alkud/OTUS_HOMEWORK_11

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/travis/build/Alkud/OTUS_HOMEWORK_11

# Include any dependencies generated for this target.
include CMakeFiles/test4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test4.dir/flags.make

CMakeFiles/test4.dir/test4.cpp.o: CMakeFiles/test4.dir/flags.make
CMakeFiles/test4.dir/test4.cpp.o: test4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test4.dir/test4.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test4.dir/test4.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/test4.cpp

CMakeFiles/test4.dir/test4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test4.dir/test4.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/test4.cpp > CMakeFiles/test4.dir/test4.cpp.i

CMakeFiles/test4.dir/test4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test4.dir/test4.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/test4.cpp -o CMakeFiles/test4.dir/test4.cpp.s

CMakeFiles/test4.dir/test4.cpp.o.requires:

.PHONY : CMakeFiles/test4.dir/test4.cpp.o.requires

CMakeFiles/test4.dir/test4.cpp.o.provides: CMakeFiles/test4.dir/test4.cpp.o.requires
	$(MAKE) -f CMakeFiles/test4.dir/build.make CMakeFiles/test4.dir/test4.cpp.o.provides.build
.PHONY : CMakeFiles/test4.dir/test4.cpp.o.provides

CMakeFiles/test4.dir/test4.cpp.o.provides.build: CMakeFiles/test4.dir/test4.cpp.o


# Object files for target test4
test4_OBJECTS = \
"CMakeFiles/test4.dir/test4.cpp.o"

# External object files for target test4
test4_EXTERNAL_OBJECTS =

test4: CMakeFiles/test4.dir/test4.cpp.o
test4: CMakeFiles/test4.dir/build.make
test4: async_command_processor/libasync.so.0.0.52
test4: CMakeFiles/test4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test4.dir/build: test4

.PHONY : CMakeFiles/test4.dir/build

CMakeFiles/test4.dir/requires: CMakeFiles/test4.dir/test4.cpp.o.requires

.PHONY : CMakeFiles/test4.dir/requires

CMakeFiles/test4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test4.dir/clean

CMakeFiles/test4.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles/test4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test4.dir/depend

