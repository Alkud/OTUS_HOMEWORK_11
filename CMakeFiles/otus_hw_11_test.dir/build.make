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
include CMakeFiles/otus_hw_11_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/otus_hw_11_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/otus_hw_11_test.dir/flags.make

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o: CMakeFiles/otus_hw_11_test.dir/flags.make
CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o: otus_hw_11_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/otus_hw_11_test.cpp

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/otus_hw_11_test.cpp > CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.i

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/otus_hw_11_test.cpp -o CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.s

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.requires:

.PHONY : CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.requires

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.provides: CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/otus_hw_11_test.dir/build.make CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.provides.build
.PHONY : CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.provides

CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.provides.build: CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o


CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o: CMakeFiles/otus_hw_11_test.dir/flags.make
CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o: homework_11.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp

CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp > CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.i

CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp -o CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.s

CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.requires:

.PHONY : CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.requires

CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.provides: CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.requires
	$(MAKE) -f CMakeFiles/otus_hw_11_test.dir/build.make CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.provides.build
.PHONY : CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.provides

CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.provides.build: CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o


# Object files for target otus_hw_11_test
otus_hw_11_test_OBJECTS = \
"CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o" \
"CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o"

# External object files for target otus_hw_11_test
otus_hw_11_test_EXTERNAL_OBJECTS =

otus_hw_11_test: CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o
otus_hw_11_test: CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o
otus_hw_11_test: CMakeFiles/otus_hw_11_test.dir/build.make
otus_hw_11_test: async_command_processor/libasync.so.0.0.39
otus_hw_11_test: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so
otus_hw_11_test: CMakeFiles/otus_hw_11_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable otus_hw_11_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/otus_hw_11_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/otus_hw_11_test.dir/build: otus_hw_11_test

.PHONY : CMakeFiles/otus_hw_11_test.dir/build

CMakeFiles/otus_hw_11_test.dir/requires: CMakeFiles/otus_hw_11_test.dir/otus_hw_11_test.cpp.o.requires
CMakeFiles/otus_hw_11_test.dir/requires: CMakeFiles/otus_hw_11_test.dir/homework_11.cpp.o.requires

.PHONY : CMakeFiles/otus_hw_11_test.dir/requires

CMakeFiles/otus_hw_11_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/otus_hw_11_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/otus_hw_11_test.dir/clean

CMakeFiles/otus_hw_11_test.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles/otus_hw_11_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/otus_hw_11_test.dir/depend

