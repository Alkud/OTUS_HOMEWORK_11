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
include async_command_processor/CMakeFiles/async.dir/depend.make

# Include the progress variables for this target.
include async_command_processor/CMakeFiles/async.dir/progress.make

# Include the compile flags for this target's objects.
include async_command_processor/CMakeFiles/async.dir/flags.make

async_command_processor/CMakeFiles/async.dir/async.cpp.o: async_command_processor/CMakeFiles/async.dir/flags.make
async_command_processor/CMakeFiles/async.dir/async.cpp.o: async_command_processor/async.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object async_command_processor/CMakeFiles/async.dir/async.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/async.dir/async.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/async.cpp

async_command_processor/CMakeFiles/async.dir/async.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/async.dir/async.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/async.cpp > CMakeFiles/async.dir/async.cpp.i

async_command_processor/CMakeFiles/async.dir/async.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/async.dir/async.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/async.cpp -o CMakeFiles/async.dir/async.cpp.s

async_command_processor/CMakeFiles/async.dir/async.cpp.o.requires:

.PHONY : async_command_processor/CMakeFiles/async.dir/async.cpp.o.requires

async_command_processor/CMakeFiles/async.dir/async.cpp.o.provides: async_command_processor/CMakeFiles/async.dir/async.cpp.o.requires
	$(MAKE) -f async_command_processor/CMakeFiles/async.dir/build.make async_command_processor/CMakeFiles/async.dir/async.cpp.o.provides.build
.PHONY : async_command_processor/CMakeFiles/async.dir/async.cpp.o.provides

async_command_processor/CMakeFiles/async.dir/async.cpp.o.provides.build: async_command_processor/CMakeFiles/async.dir/async.cpp.o


async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o: async_command_processor/CMakeFiles/async.dir/flags.make
async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o: async_command_processor/input_processor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/async.dir/input_processor.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_processor.cpp

async_command_processor/CMakeFiles/async.dir/input_processor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/async.dir/input_processor.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_processor.cpp > CMakeFiles/async.dir/input_processor.cpp.i

async_command_processor/CMakeFiles/async.dir/input_processor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/async.dir/input_processor.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_processor.cpp -o CMakeFiles/async.dir/input_processor.cpp.s

async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.requires:

.PHONY : async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.requires

async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.provides: async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.requires
	$(MAKE) -f async_command_processor/CMakeFiles/async.dir/build.make async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.provides.build
.PHONY : async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.provides

async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.provides.build: async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o


async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o: async_command_processor/CMakeFiles/async.dir/flags.make
async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o: async_command_processor/input_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/async.dir/input_reader.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_reader.cpp

async_command_processor/CMakeFiles/async.dir/input_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/async.dir/input_reader.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_reader.cpp > CMakeFiles/async.dir/input_reader.cpp.i

async_command_processor/CMakeFiles/async.dir/input_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/async.dir/input_reader.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/input_reader.cpp -o CMakeFiles/async.dir/input_reader.cpp.s

async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.requires:

.PHONY : async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.requires

async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.provides: async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.requires
	$(MAKE) -f async_command_processor/CMakeFiles/async.dir/build.make async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.provides.build
.PHONY : async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.provides

async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.provides.build: async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o


async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o: async_command_processor/CMakeFiles/async.dir/flags.make
async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o: async_command_processor/publisher_mt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/async.dir/publisher_mt.cpp.o -c /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/publisher_mt.cpp

async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/async.dir/publisher_mt.cpp.i"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/publisher_mt.cpp > CMakeFiles/async.dir/publisher_mt.cpp.i

async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/async.dir/publisher_mt.cpp.s"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/publisher_mt.cpp -o CMakeFiles/async.dir/publisher_mt.cpp.s

async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.requires:

.PHONY : async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.requires

async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.provides: async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.requires
	$(MAKE) -f async_command_processor/CMakeFiles/async.dir/build.make async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.provides.build
.PHONY : async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.provides

async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.provides.build: async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o


# Object files for target async
async_OBJECTS = \
"CMakeFiles/async.dir/async.cpp.o" \
"CMakeFiles/async.dir/input_processor.cpp.o" \
"CMakeFiles/async.dir/input_reader.cpp.o" \
"CMakeFiles/async.dir/publisher_mt.cpp.o"

# External object files for target async
async_EXTERNAL_OBJECTS =

async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/async.cpp.o
async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o
async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o
async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o
async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/build.make
async_command_processor/libasync.so.0.0.6: async_command_processor/CMakeFiles/async.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/travis/build/Alkud/OTUS_HOMEWORK_11/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libasync.so"
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/async.dir/link.txt --verbose=$(VERBOSE)
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && $(CMAKE_COMMAND) -E cmake_symlink_library libasync.so.0.0.6 libasync.so.0.0.6 libasync.so

async_command_processor/libasync.so: async_command_processor/libasync.so.0.0.6
	@$(CMAKE_COMMAND) -E touch_nocreate async_command_processor/libasync.so

# Rule to build all files generated by this target.
async_command_processor/CMakeFiles/async.dir/build: async_command_processor/libasync.so

.PHONY : async_command_processor/CMakeFiles/async.dir/build

async_command_processor/CMakeFiles/async.dir/requires: async_command_processor/CMakeFiles/async.dir/async.cpp.o.requires
async_command_processor/CMakeFiles/async.dir/requires: async_command_processor/CMakeFiles/async.dir/input_processor.cpp.o.requires
async_command_processor/CMakeFiles/async.dir/requires: async_command_processor/CMakeFiles/async.dir/input_reader.cpp.o.requires
async_command_processor/CMakeFiles/async.dir/requires: async_command_processor/CMakeFiles/async.dir/publisher_mt.cpp.o.requires

.PHONY : async_command_processor/CMakeFiles/async.dir/requires

async_command_processor/CMakeFiles/async.dir/clean:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor && $(CMAKE_COMMAND) -P CMakeFiles/async.dir/cmake_clean.cmake
.PHONY : async_command_processor/CMakeFiles/async.dir/clean

async_command_processor/CMakeFiles/async.dir/depend:
	cd /home/travis/build/Alkud/OTUS_HOMEWORK_11 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor /home/travis/build/Alkud/OTUS_HOMEWORK_11 /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor /home/travis/build/Alkud/OTUS_HOMEWORK_11/async_command_processor/CMakeFiles/async.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : async_command_processor/CMakeFiles/async.dir/depend

