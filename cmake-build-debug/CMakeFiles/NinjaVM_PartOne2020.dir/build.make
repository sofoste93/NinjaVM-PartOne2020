# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Dell\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7717.62\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Dell\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\203.7717.62\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NinjaVM_PartOne2020.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NinjaVM_PartOne2020.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NinjaVM_PartOne2020.dir/flags.make

CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj: CMakeFiles/NinjaVM_PartOne2020.dir/flags.make
CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj: CMakeFiles/NinjaVM_PartOne2020.dir/includes_C.rsp
CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj: ../njvm4.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\NinjaVM_PartOne2020.dir\njvm4.c.obj   -c C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\njvm4.c

CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\njvm4.c > CMakeFiles\NinjaVM_PartOne2020.dir\njvm4.c.i

CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\njvm4.c -o CMakeFiles\NinjaVM_PartOne2020.dir\njvm4.c.s

# Object files for target NinjaVM_PartOne2020
NinjaVM_PartOne2020_OBJECTS = \
"CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj"

# External object files for target NinjaVM_PartOne2020
NinjaVM_PartOne2020_EXTERNAL_OBJECTS =

NinjaVM_PartOne2020.exe: CMakeFiles/NinjaVM_PartOne2020.dir/njvm4.c.obj
NinjaVM_PartOne2020.exe: CMakeFiles/NinjaVM_PartOne2020.dir/build.make
NinjaVM_PartOne2020.exe: CMakeFiles/NinjaVM_PartOne2020.dir/linklibs.rsp
NinjaVM_PartOne2020.exe: CMakeFiles/NinjaVM_PartOne2020.dir/objects1.rsp
NinjaVM_PartOne2020.exe: CMakeFiles/NinjaVM_PartOne2020.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable NinjaVM_PartOne2020.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\NinjaVM_PartOne2020.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NinjaVM_PartOne2020.dir/build: NinjaVM_PartOne2020.exe

.PHONY : CMakeFiles/NinjaVM_PartOne2020.dir/build

CMakeFiles/NinjaVM_PartOne2020.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\NinjaVM_PartOne2020.dir\cmake_clean.cmake
.PHONY : CMakeFiles/NinjaVM_PartOne2020.dir/clean

CMakeFiles/NinjaVM_PartOne2020.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020 C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020 C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug C:\Users\Dell\CLionProjects\NinjaVM-PartOne2020\cmake-build-debug\CMakeFiles\NinjaVM_PartOne2020.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NinjaVM_PartOne2020.dir/depend

