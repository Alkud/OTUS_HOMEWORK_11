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
include CMakeFiles/bulkasync.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bulkasync.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bulkasync.dir/flags.make

CMakeFiles/bulkasync.dir/bulkasync.cpp.o: CMakeFiles/bulkasync.dir/flags.make
CMakeFiles/bulkasync.dir/bulkasync.cpp.o: bulkasync.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bulkasync.dir/bulkasync.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bulkasync.dir/bulkasync.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/bulkasync.cpp

CMakeFiles/bulkasync.dir/bulkasync.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bulkasync.dir/bulkasync.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/bulkasync.cpp > CMakeFiles/bulkasync.dir/bulkasync.cpp.i

CMakeFiles/bulkasync.dir/bulkasync.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bulkasync.dir/bulkasync.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/bulkasync.cpp -o CMakeFiles/bulkasync.dir/bulkasync.cpp.s

CMakeFiles/bulkasync.dir/bulkasync.cpp.o.requires:

.PHONY : CMakeFiles/bulkasync.dir/bulkasync.cpp.o.requires

CMakeFiles/bulkasync.dir/bulkasync.cpp.o.provides: CMakeFiles/bulkasync.dir/bulkasync.cpp.o.requires
	$(MAKE) -f CMakeFiles/bulkasync.dir/build.make CMakeFiles/bulkasync.dir/bulkasync.cpp.o.provides.build
.PHONY : CMakeFiles/bulkasync.dir/bulkasync.cpp.o.provides

CMakeFiles/bulkasync.dir/bulkasync.cpp.o.provides.build: CMakeFiles/bulkasync.dir/bulkasync.cpp.o


CMakeFiles/bulkasync.dir/homework_11.cpp.o: CMakeFiles/bulkasync.dir/flags.make
CMakeFiles/bulkasync.dir/homework_11.cpp.o: homework_11.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/bulkasync.dir/homework_11.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bulkasync.dir/homework_11.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp

CMakeFiles/bulkasync.dir/homework_11.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bulkasync.dir/homework_11.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp > CMakeFiles/bulkasync.dir/homework_11.cpp.i

CMakeFiles/bulkasync.dir/homework_11.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bulkasync.dir/homework_11.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/homework_11.cpp -o CMakeFiles/bulkasync.dir/homework_11.cpp.s

CMakeFiles/bulkasync.dir/homework_11.cpp.o.requires:

.PHONY : CMakeFiles/bulkasync.dir/homework_11.cpp.o.requires

CMakeFiles/bulkasync.dir/homework_11.cpp.o.provides: CMakeFiles/bulkasync.dir/homework_11.cpp.o.requires
	$(MAKE) -f CMakeFiles/bulkasync.dir/build.make CMakeFiles/bulkasync.dir/homework_11.cpp.o.provides.build
.PHONY : CMakeFiles/bulkasync.dir/homework_11.cpp.o.provides

CMakeFiles/bulkasync.dir/homework_11.cpp.o.provides.build: CMakeFiles/bulkasync.dir/homework_11.cpp.o


# Object files for target bulkasync
bulkasync_OBJECTS = \
"CMakeFiles/bulkasync.dir/bulkasync.cpp.o" \
"CMakeFiles/bulkasync.dir/homework_11.cpp.o"

# External object files for target bulkasync
bulkasync_EXTERNAL_OBJECTS =

bulkasync: CMakeFiles/bulkasync.dir/bulkasync.cpp.o
bulkasync: CMakeFiles/bulkasync.dir/homework_11.cpp.o
bulkasync: CMakeFiles/bulkasync.dir/build.make
bulkasync: async_command_processor/libasync.so.0.0.38
bulkasync: CMakeFiles/bulkasync.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bulkasync"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bulkasync.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bulkasync.dir/build: bulkasync

.PHONY : CMakeFiles/bulkasync.dir/build

CMakeFiles/bulkasync.dir/requires: CMakeFiles/bulkasync.dir/bulkasync.cpp.o.requires
CMakeFiles/bulkasync.dir/requires: CMakeFiles/bulkasync.dir/homework_11.cpp.o.requires

.PHONY : CMakeFiles/bulkasync.dir/requires

CMakeFiles/bulkasync.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bulkasync.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bulkasync.dir/clean

CMakeFiles/bulkasync.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles/bulkasync.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bulkasync.dir/depend

