# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src

# Utility rule file for TameCalc_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/TameCalc_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TameCalc_autogen.dir/progress.make

CMakeFiles/TameCalc_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/tamelabe/Documents/repo/CPP3_SmartCalc/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target TameCalc"
	/Applications/CMake.app/Contents/bin/cmake -E cmake_autogen /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src/CMakeFiles/TameCalc_autogen.dir/AutogenInfo.json Debug

TameCalc_autogen: CMakeFiles/TameCalc_autogen
TameCalc_autogen: CMakeFiles/TameCalc_autogen.dir/build.make
.PHONY : TameCalc_autogen

# Rule to build all files generated by this target.
CMakeFiles/TameCalc_autogen.dir/build: TameCalc_autogen
.PHONY : CMakeFiles/TameCalc_autogen.dir/build

CMakeFiles/TameCalc_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TameCalc_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TameCalc_autogen.dir/clean

CMakeFiles/TameCalc_autogen.dir/depend:
	cd /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src /Users/tamelabe/Documents/repo/CPP3_SmartCalc/src/CMakeFiles/TameCalc_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TameCalc_autogen.dir/depend
