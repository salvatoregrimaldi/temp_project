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
include CMakeFiles/eseguibileO1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/eseguibileO1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/eseguibileO1.dir/flags.make

CMakeFiles/eseguibileO1.dir/src/main.c.o: CMakeFiles/eseguibileO1.dir/flags.make
CMakeFiles/eseguibileO1.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/eseguibileO1.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eseguibileO1.dir/src/main.c.o   -c /mnt/c/Users/Salvatore/Desktop/temp_project/src/main.c

CMakeFiles/eseguibileO1.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eseguibileO1.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Salvatore/Desktop/temp_project/src/main.c > CMakeFiles/eseguibileO1.dir/src/main.c.i

CMakeFiles/eseguibileO1.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eseguibileO1.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Salvatore/Desktop/temp_project/src/main.c -o CMakeFiles/eseguibileO1.dir/src/main.c.s

CMakeFiles/eseguibileO1.dir/src/countingsort.c.o: CMakeFiles/eseguibileO1.dir/flags.make
CMakeFiles/eseguibileO1.dir/src/countingsort.c.o: ../src/countingsort.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/eseguibileO1.dir/src/countingsort.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/eseguibileO1.dir/src/countingsort.c.o   -c /mnt/c/Users/Salvatore/Desktop/temp_project/src/countingsort.c

CMakeFiles/eseguibileO1.dir/src/countingsort.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/eseguibileO1.dir/src/countingsort.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Salvatore/Desktop/temp_project/src/countingsort.c > CMakeFiles/eseguibileO1.dir/src/countingsort.c.i

CMakeFiles/eseguibileO1.dir/src/countingsort.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/eseguibileO1.dir/src/countingsort.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Salvatore/Desktop/temp_project/src/countingsort.c -o CMakeFiles/eseguibileO1.dir/src/countingsort.c.s

# Object files for target eseguibileO1
eseguibileO1_OBJECTS = \
"CMakeFiles/eseguibileO1.dir/src/main.c.o" \
"CMakeFiles/eseguibileO1.dir/src/countingsort.c.o"

# External object files for target eseguibileO1
eseguibileO1_EXTERNAL_OBJECTS =

eseguibileO1: CMakeFiles/eseguibileO1.dir/src/main.c.o
eseguibileO1: CMakeFiles/eseguibileO1.dir/src/countingsort.c.o
eseguibileO1: CMakeFiles/eseguibileO1.dir/build.make
eseguibileO1: /usr/lib/x86_64-linux-gnu/libmpich.so
eseguibileO1: CMakeFiles/eseguibileO1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable eseguibileO1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/eseguibileO1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/eseguibileO1.dir/build: eseguibileO1

.PHONY : CMakeFiles/eseguibileO1.dir/build

CMakeFiles/eseguibileO1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/eseguibileO1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/eseguibileO1.dir/clean

CMakeFiles/eseguibileO1.dir/depend:
	cd /mnt/c/Users/Salvatore/Desktop/temp_project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Salvatore/Desktop/temp_project /mnt/c/Users/Salvatore/Desktop/temp_project /mnt/c/Users/Salvatore/Desktop/temp_project/build /mnt/c/Users/Salvatore/Desktop/temp_project/build /mnt/c/Users/Salvatore/Desktop/temp_project/build/CMakeFiles/eseguibileO1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/eseguibileO1.dir/depend

