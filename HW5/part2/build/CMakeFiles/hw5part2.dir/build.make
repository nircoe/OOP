# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/mtm/cmake-3.17.0-Linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nir-nisim-co/OOP/HW5/part2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nir-nisim-co/OOP/HW5/part2/build

# Include any dependencies generated for this target.
include CMakeFiles/hw5part2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw5part2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw5part2.dir/flags.make

CMakeFiles/hw5part2.dir/RushHourTests.cpp.o: CMakeFiles/hw5part2.dir/flags.make
CMakeFiles/hw5part2.dir/RushHourTests.cpp.o: ../RushHourTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nir-nisim-co/OOP/HW5/part2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw5part2.dir/RushHourTests.cpp.o"
	/usr/local/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw5part2.dir/RushHourTests.cpp.o -c /home/nir-nisim-co/OOP/HW5/part2/RushHourTests.cpp

CMakeFiles/hw5part2.dir/RushHourTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw5part2.dir/RushHourTests.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nir-nisim-co/OOP/HW5/part2/RushHourTests.cpp > CMakeFiles/hw5part2.dir/RushHourTests.cpp.i

CMakeFiles/hw5part2.dir/RushHourTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw5part2.dir/RushHourTests.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nir-nisim-co/OOP/HW5/part2/RushHourTests.cpp -o CMakeFiles/hw5part2.dir/RushHourTests.cpp.s

# Object files for target hw5part2
hw5part2_OBJECTS = \
"CMakeFiles/hw5part2.dir/RushHourTests.cpp.o"

# External object files for target hw5part2
hw5part2_EXTERNAL_OBJECTS =

hw5part2: CMakeFiles/hw5part2.dir/RushHourTests.cpp.o
hw5part2: CMakeFiles/hw5part2.dir/build.make
hw5part2: CMakeFiles/hw5part2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nir-nisim-co/OOP/HW5/part2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw5part2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw5part2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw5part2.dir/build: hw5part2

.PHONY : CMakeFiles/hw5part2.dir/build

CMakeFiles/hw5part2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw5part2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw5part2.dir/clean

CMakeFiles/hw5part2.dir/depend:
	cd /home/nir-nisim-co/OOP/HW5/part2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nir-nisim-co/OOP/HW5/part2 /home/nir-nisim-co/OOP/HW5/part2 /home/nir-nisim-co/OOP/HW5/part2/build /home/nir-nisim-co/OOP/HW5/part2/build /home/nir-nisim-co/OOP/HW5/part2/build/CMakeFiles/hw5part2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw5part2.dir/depend

