# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build

# Include any dependencies generated for this target.
include examples/CMakeFiles/10-colors-main.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/10-colors-main.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/10-colors-main.dir/flags.make

examples/CMakeFiles/10-colors-main.dir/main.c.o: examples/CMakeFiles/10-colors-main.dir/flags.make
examples/CMakeFiles/10-colors-main.dir/main.c.o: ../10-colors/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object examples/CMakeFiles/10-colors-main.dir/main.c.o"
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/10-colors-main.dir/main.c.o   -c /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/10-colors/main.c

examples/CMakeFiles/10-colors-main.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/10-colors-main.dir/main.c.i"
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/10-colors/main.c > CMakeFiles/10-colors-main.dir/main.c.i

examples/CMakeFiles/10-colors-main.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/10-colors-main.dir/main.c.s"
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/10-colors/main.c -o CMakeFiles/10-colors-main.dir/main.c.s

examples/CMakeFiles/10-colors-main.dir/main.c.o.requires:

.PHONY : examples/CMakeFiles/10-colors-main.dir/main.c.o.requires

examples/CMakeFiles/10-colors-main.dir/main.c.o.provides: examples/CMakeFiles/10-colors-main.dir/main.c.o.requires
	$(MAKE) -f examples/CMakeFiles/10-colors-main.dir/build.make examples/CMakeFiles/10-colors-main.dir/main.c.o.provides.build
.PHONY : examples/CMakeFiles/10-colors-main.dir/main.c.o.provides

examples/CMakeFiles/10-colors-main.dir/main.c.o.provides.build: examples/CMakeFiles/10-colors-main.dir/main.c.o


# Object files for target 10-colors-main
10__colors__main_OBJECTS = \
"CMakeFiles/10-colors-main.dir/main.c.o"

# External object files for target 10-colors-main
10__colors__main_EXTERNAL_OBJECTS =

examples/10-colors-main: examples/CMakeFiles/10-colors-main.dir/main.c.o
examples/10-colors-main: examples/CMakeFiles/10-colors-main.dir/build.make
examples/10-colors-main: /usr/lib/x86_64-linux-gnu/libcurses.so
examples/10-colors-main: examples/CMakeFiles/10-colors-main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 10-colors-main"
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/10-colors-main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/10-colors-main.dir/build: examples/10-colors-main

.PHONY : examples/CMakeFiles/10-colors-main.dir/build

examples/CMakeFiles/10-colors-main.dir/requires: examples/CMakeFiles/10-colors-main.dir/main.c.o.requires

.PHONY : examples/CMakeFiles/10-colors-main.dir/requires

examples/CMakeFiles/10-colors-main.dir/clean:
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples && $(CMAKE_COMMAND) -P CMakeFiles/10-colors-main.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/10-colors-main.dir/clean

examples/CMakeFiles/10-colors-main.dir/depend:
	cd /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/10-colors /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples /home/bcc/rrs17/Matérias/segundoSemestre/Oficina/projetos/IsaacGame/teste/teste/NCURSES-Programming-HOWTO-examples/build/examples/CMakeFiles/10-colors-main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/CMakeFiles/10-colors-main.dir/depend

