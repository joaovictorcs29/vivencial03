# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/joaov/Documents/processamentoGrafico6

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/joaov/Documents/processamentoGrafico6/build

# Include any dependencies generated for this target.
include CMakeFiles/spriteMoving.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/spriteMoving.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/spriteMoving.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/spriteMoving.dir/flags.make

CMakeFiles/spriteMoving.dir/codegen:
.PHONY : CMakeFiles/spriteMoving.dir/codegen

CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj: CMakeFiles/spriteMoving.dir/flags.make
CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj: CMakeFiles/spriteMoving.dir/includes_CXX.rsp
CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj: C:/Users/joaov/Documents/processamentoGrafico6/src/spriteMoving.cpp
CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj: CMakeFiles/spriteMoving.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Users/joaov/Documents/processamentoGrafico6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj"
	C:/msys64/ucrt64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj -MF CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj.d -o CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj -c C:/Users/joaov/Documents/processamentoGrafico6/src/spriteMoving.cpp

CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.i"
	C:/msys64/ucrt64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/joaov/Documents/processamentoGrafico6/src/spriteMoving.cpp > CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.i

CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.s"
	C:/msys64/ucrt64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/joaov/Documents/processamentoGrafico6/src/spriteMoving.cpp -o CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.s

CMakeFiles/spriteMoving.dir/common/glad.c.obj: CMakeFiles/spriteMoving.dir/flags.make
CMakeFiles/spriteMoving.dir/common/glad.c.obj: CMakeFiles/spriteMoving.dir/includes_C.rsp
CMakeFiles/spriteMoving.dir/common/glad.c.obj: C:/Users/joaov/Documents/processamentoGrafico6/common/glad.c
CMakeFiles/spriteMoving.dir/common/glad.c.obj: CMakeFiles/spriteMoving.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Users/joaov/Documents/processamentoGrafico6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/spriteMoving.dir/common/glad.c.obj"
	C:/msys64/ucrt64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/spriteMoving.dir/common/glad.c.obj -MF CMakeFiles/spriteMoving.dir/common/glad.c.obj.d -o CMakeFiles/spriteMoving.dir/common/glad.c.obj -c C:/Users/joaov/Documents/processamentoGrafico6/common/glad.c

CMakeFiles/spriteMoving.dir/common/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/spriteMoving.dir/common/glad.c.i"
	C:/msys64/ucrt64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:/Users/joaov/Documents/processamentoGrafico6/common/glad.c > CMakeFiles/spriteMoving.dir/common/glad.c.i

CMakeFiles/spriteMoving.dir/common/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/spriteMoving.dir/common/glad.c.s"
	C:/msys64/ucrt64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:/Users/joaov/Documents/processamentoGrafico6/common/glad.c -o CMakeFiles/spriteMoving.dir/common/glad.c.s

# Object files for target spriteMoving
spriteMoving_OBJECTS = \
"CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj" \
"CMakeFiles/spriteMoving.dir/common/glad.c.obj"

# External object files for target spriteMoving
spriteMoving_EXTERNAL_OBJECTS =

spriteMoving.exe: CMakeFiles/spriteMoving.dir/src/spriteMoving.cpp.obj
spriteMoving.exe: CMakeFiles/spriteMoving.dir/common/glad.c.obj
spriteMoving.exe: CMakeFiles/spriteMoving.dir/build.make
spriteMoving.exe: _deps/glfw-build/src/libglfw3.a
spriteMoving.exe: _deps/glm-build/glm/libglm.a
spriteMoving.exe: CMakeFiles/spriteMoving.dir/linkLibs.rsp
spriteMoving.exe: CMakeFiles/spriteMoving.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/Users/joaov/Documents/processamentoGrafico6/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable spriteMoving.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/spriteMoving.dir/objects.a
	C:/msys64/ucrt64/bin/ar.exe qc CMakeFiles/spriteMoving.dir/objects.a @CMakeFiles/spriteMoving.dir/objects1.rsp
	C:/msys64/ucrt64/bin/g++.exe -g -Wl,--whole-archive CMakeFiles/spriteMoving.dir/objects.a -Wl,--no-whole-archive -o spriteMoving.exe -Wl,--out-implib,libspriteMoving.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/spriteMoving.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/spriteMoving.dir/build: spriteMoving.exe
.PHONY : CMakeFiles/spriteMoving.dir/build

CMakeFiles/spriteMoving.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/spriteMoving.dir/cmake_clean.cmake
.PHONY : CMakeFiles/spriteMoving.dir/clean

CMakeFiles/spriteMoving.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/joaov/Documents/processamentoGrafico6 C:/Users/joaov/Documents/processamentoGrafico6 C:/Users/joaov/Documents/processamentoGrafico6/build C:/Users/joaov/Documents/processamentoGrafico6/build C:/Users/joaov/Documents/processamentoGrafico6/build/CMakeFiles/spriteMoving.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/spriteMoving.dir/depend

