# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/alex/Kangaeru/Kangaeru

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Kangaeru/Kangaeru/linux-build

# Include any dependencies generated for this target.
include cocos2d/external/xxhash/CMakeFiles/xxhash.dir/depend.make

# Include the progress variables for this target.
include cocos2d/external/xxhash/CMakeFiles/xxhash.dir/progress.make

# Include the compile flags for this target's objects.
include cocos2d/external/xxhash/CMakeFiles/xxhash.dir/flags.make

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/flags.make
cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o: ../cocos2d/external/xxhash/xxhash.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/alex/Kangaeru/Kangaeru/linux-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o"
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/xxhash.dir/xxhash.c.o   -c /home/alex/Kangaeru/Kangaeru/cocos2d/external/xxhash/xxhash.c

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/xxhash.dir/xxhash.c.i"
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -E /home/alex/Kangaeru/Kangaeru/cocos2d/external/xxhash/xxhash.c > CMakeFiles/xxhash.dir/xxhash.c.i

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/xxhash.dir/xxhash.c.s"
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && /usr/bin/cc  $(C_DEFINES) $(C_FLAGS) -S /home/alex/Kangaeru/Kangaeru/cocos2d/external/xxhash/xxhash.c -o CMakeFiles/xxhash.dir/xxhash.c.s

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.requires:
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.requires

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.provides: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.requires
	$(MAKE) -f cocos2d/external/xxhash/CMakeFiles/xxhash.dir/build.make cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.provides.build
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.provides

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.provides.build: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o

# Object files for target xxhash
xxhash_OBJECTS = \
"CMakeFiles/xxhash.dir/xxhash.c.o"

# External object files for target xxhash
xxhash_EXTERNAL_OBJECTS =

lib/libxxhash.a: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o
lib/libxxhash.a: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/build.make
lib/libxxhash.a: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C static library ../../../lib/libxxhash.a"
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && $(CMAKE_COMMAND) -P CMakeFiles/xxhash.dir/cmake_clean_target.cmake
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/xxhash.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
cocos2d/external/xxhash/CMakeFiles/xxhash.dir/build: lib/libxxhash.a
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/build

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/requires: cocos2d/external/xxhash/CMakeFiles/xxhash.dir/xxhash.c.o.requires
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/requires

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/clean:
	cd /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash && $(CMAKE_COMMAND) -P CMakeFiles/xxhash.dir/cmake_clean.cmake
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/clean

cocos2d/external/xxhash/CMakeFiles/xxhash.dir/depend:
	cd /home/alex/Kangaeru/Kangaeru/linux-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Kangaeru/Kangaeru /home/alex/Kangaeru/Kangaeru/cocos2d/external/xxhash /home/alex/Kangaeru/Kangaeru/linux-build /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash /home/alex/Kangaeru/Kangaeru/linux-build/cocos2d/external/xxhash/CMakeFiles/xxhash.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : cocos2d/external/xxhash/CMakeFiles/xxhash.dir/depend

