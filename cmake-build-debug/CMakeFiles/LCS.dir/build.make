# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CLion\bin\cmake\win\x64\bin\cmake.exe

# The command to remove a file.
RM = D:\CLion\bin\cmake\win\x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\CLion\Cpp_Development-Engineer_Data-Structure

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LCS.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LCS.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LCS.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LCS.dir/flags.make

CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj: CMakeFiles/LCS.dir/flags.make
CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj: F:/CLion/Cpp_Development-Engineer_Data-Structure/32_DynamicProgrammingAlgorithm/LCS.cpp
CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj: CMakeFiles/LCS.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj -MF CMakeFiles\LCS.dir\32_DynamicProgrammingAlgorithm\LCS.cpp.obj.d -o CMakeFiles\LCS.dir\32_DynamicProgrammingAlgorithm\LCS.cpp.obj -c F:\CLion\Cpp_Development-Engineer_Data-Structure\32_DynamicProgrammingAlgorithm\LCS.cpp

CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CLion\Cpp_Development-Engineer_Data-Structure\32_DynamicProgrammingAlgorithm\LCS.cpp > CMakeFiles\LCS.dir\32_DynamicProgrammingAlgorithm\LCS.cpp.i

CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CLion\Cpp_Development-Engineer_Data-Structure\32_DynamicProgrammingAlgorithm\LCS.cpp -o CMakeFiles\LCS.dir\32_DynamicProgrammingAlgorithm\LCS.cpp.s

# Object files for target LCS
LCS_OBJECTS = \
"CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj"

# External object files for target LCS
LCS_EXTERNAL_OBJECTS =

LCS.exe: CMakeFiles/LCS.dir/32_DynamicProgrammingAlgorithm/LCS.cpp.obj
LCS.exe: CMakeFiles/LCS.dir/build.make
LCS.exe: CMakeFiles/LCS.dir/linkLibs.rsp
LCS.exe: CMakeFiles/LCS.dir/objects1.rsp
LCS.exe: CMakeFiles/LCS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LCS.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LCS.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LCS.dir/build: LCS.exe
.PHONY : CMakeFiles/LCS.dir/build

CMakeFiles/LCS.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LCS.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LCS.dir/clean

CMakeFiles/LCS.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\CLion\Cpp_Development-Engineer_Data-Structure F:\CLion\Cpp_Development-Engineer_Data-Structure F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles\LCS.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/LCS.dir/depend

