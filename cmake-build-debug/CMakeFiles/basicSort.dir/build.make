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
include CMakeFiles/basicSort.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/basicSort.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/basicSort.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/basicSort.dir/flags.make

CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj: CMakeFiles/basicSort.dir/flags.make
CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj: F:/CLion/Cpp_Development-Engineer_Data-Structure/11_BasicSort/basicSort.cpp
CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj: CMakeFiles/basicSort.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj -MF CMakeFiles\basicSort.dir\11_BasicSort\basicSort.cpp.obj.d -o CMakeFiles\basicSort.dir\11_BasicSort\basicSort.cpp.obj -c F:\CLion\Cpp_Development-Engineer_Data-Structure\11_BasicSort\basicSort.cpp

CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.i"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\CLion\Cpp_Development-Engineer_Data-Structure\11_BasicSort\basicSort.cpp > CMakeFiles\basicSort.dir\11_BasicSort\basicSort.cpp.i

CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.s"
	D:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\CLion\Cpp_Development-Engineer_Data-Structure\11_BasicSort\basicSort.cpp -o CMakeFiles\basicSort.dir\11_BasicSort\basicSort.cpp.s

# Object files for target basicSort
basicSort_OBJECTS = \
"CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj"

# External object files for target basicSort
basicSort_EXTERNAL_OBJECTS =

basicSort.exe: CMakeFiles/basicSort.dir/11_BasicSort/basicSort.cpp.obj
basicSort.exe: CMakeFiles/basicSort.dir/build.make
basicSort.exe: CMakeFiles/basicSort.dir/linkLibs.rsp
basicSort.exe: CMakeFiles/basicSort.dir/objects1.rsp
basicSort.exe: CMakeFiles/basicSort.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable basicSort.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\basicSort.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/basicSort.dir/build: basicSort.exe
.PHONY : CMakeFiles/basicSort.dir/build

CMakeFiles/basicSort.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\basicSort.dir\cmake_clean.cmake
.PHONY : CMakeFiles/basicSort.dir/clean

CMakeFiles/basicSort.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\CLion\Cpp_Development-Engineer_Data-Structure F:\CLion\Cpp_Development-Engineer_Data-Structure F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug F:\CLion\Cpp_Development-Engineer_Data-Structure\cmake-build-debug\CMakeFiles\basicSort.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/basicSort.dir/depend

