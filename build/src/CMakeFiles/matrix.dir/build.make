# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build

# Include any dependencies generated for this target.
include src/CMakeFiles/matrix.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/matrix.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/matrix.dir/flags.make

src/CMakeFiles/matrix.dir/matrix.cpp.o: src/CMakeFiles/matrix.dir/flags.make
src/CMakeFiles/matrix.dir/matrix.cpp.o: ../src/matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/matrix.dir/matrix.cpp.o"
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matrix.dir/matrix.cpp.o -c /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/src/matrix.cpp

src/CMakeFiles/matrix.dir/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrix.dir/matrix.cpp.i"
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/src/matrix.cpp > CMakeFiles/matrix.dir/matrix.cpp.i

src/CMakeFiles/matrix.dir/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrix.dir/matrix.cpp.s"
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/src/matrix.cpp -o CMakeFiles/matrix.dir/matrix.cpp.s

src/CMakeFiles/matrix.dir/matrix.cpp.o.requires:

.PHONY : src/CMakeFiles/matrix.dir/matrix.cpp.o.requires

src/CMakeFiles/matrix.dir/matrix.cpp.o.provides: src/CMakeFiles/matrix.dir/matrix.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/matrix.dir/build.make src/CMakeFiles/matrix.dir/matrix.cpp.o.provides.build
.PHONY : src/CMakeFiles/matrix.dir/matrix.cpp.o.provides

src/CMakeFiles/matrix.dir/matrix.cpp.o.provides.build: src/CMakeFiles/matrix.dir/matrix.cpp.o


# Object files for target matrix
matrix_OBJECTS = \
"CMakeFiles/matrix.dir/matrix.cpp.o"

# External object files for target matrix
matrix_EXTERNAL_OBJECTS =

src/libmatrix.a: src/CMakeFiles/matrix.dir/matrix.cpp.o
src/libmatrix.a: src/CMakeFiles/matrix.dir/build.make
src/libmatrix.a: src/CMakeFiles/matrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmatrix.a"
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && $(CMAKE_COMMAND) -P CMakeFiles/matrix.dir/cmake_clean_target.cmake
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/matrix.dir/build: src/libmatrix.a

.PHONY : src/CMakeFiles/matrix.dir/build

src/CMakeFiles/matrix.dir/requires: src/CMakeFiles/matrix.dir/matrix.cpp.o.requires

.PHONY : src/CMakeFiles/matrix.dir/requires

src/CMakeFiles/matrix.dir/clean:
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src && $(CMAKE_COMMAND) -P CMakeFiles/matrix.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/matrix.dir/clean

src/CMakeFiles/matrix.dir/depend:
	cd /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/src /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src /Users/patrickmintram/Documents/Programming/C++/MatrixMaths/MatrixMaths/build/src/CMakeFiles/matrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/matrix.dir/depend

