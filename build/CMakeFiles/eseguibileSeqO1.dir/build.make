# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Salvatore/Desktop/temp_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Salvatore/Desktop/temp_project/build

# Include any dependencies generated for this target.
include CMakeFiles/eseguibileSeqO1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eseguibileSeqO1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eseguibileSeqO1.dir/flags.make

CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o: CMakeFiles/eseguibileSeqO1.dir/flags.make
CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o: ../src/mainS.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o   -c /mnt/c/Users/Salvatore/Desktop/temp_project/src/mainS.c

CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Salvatore/Desktop/temp_project/src/mainS.c > CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.i

CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Salvatore/Desktop/temp_project/src/mainS.c -o CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.s

# Object files for target eseguibileSeqO1
eseguibileSeqO1_OBJECTS = \
"CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o"

# External object files for target eseguibileSeqO1
eseguibileSeqO1_EXTERNAL_OBJECTS =

eseguibileSeqO1: CMakeFiles/eseguibileSeqO1.dir/src/mainS.c.o
eseguibileSeqO1: CMakeFiles/eseguibileSeqO1.dir/build.make
eseguibileSeqO1: CMakeFiles/eseguibileSeqO1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable eseguibileSeqO1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eseguibileSeqO1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eseguibileSeqO1.dir/build: eseguibileSeqO1

.PHONY : CMakeFiles/eseguibileSeqO1.dir/build

CMakeFiles/eseguibileSeqO1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eseguibileSeqO1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eseguibileSeqO1.dir/clean

CMakeFiles/eseguibileSeqO1.dir/depend:
	cd /mnt/c/Users/Salvatore/Desktop/temp_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Salvatore/Desktop/temp_project /mnt/c/Users/Salvatore/Desktop/temp_project /mnt/c/Users/Salvatore/Desktop/temp_project/build /mnt/c/Users/Salvatore/Desktop/temp_project/build /mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles/eseguibileSeqO1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eseguibileSeqO1.dir/depend
