# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/PokemonBattle.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/PokemonBattle.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/PokemonBattle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PokemonBattle.dir/flags.make

CMakeFiles/PokemonBattle.dir/main.cpp.obj: CMakeFiles/PokemonBattle.dir/flags.make
CMakeFiles/PokemonBattle.dir/main.cpp.obj: ../main.cpp
CMakeFiles/PokemonBattle.dir/main.cpp.obj: CMakeFiles/PokemonBattle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PokemonBattle.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PokemonBattle.dir/main.cpp.obj -MF CMakeFiles\PokemonBattle.dir\main.cpp.obj.d -o CMakeFiles\PokemonBattle.dir\main.cpp.obj -c "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\main.cpp"

CMakeFiles/PokemonBattle.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PokemonBattle.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\main.cpp" > CMakeFiles\PokemonBattle.dir\main.cpp.i

CMakeFiles/PokemonBattle.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PokemonBattle.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\main.cpp" -o CMakeFiles\PokemonBattle.dir\main.cpp.s

CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj: CMakeFiles/PokemonBattle.dir/flags.make
CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj: ../Pokemon.cpp
CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj: CMakeFiles/PokemonBattle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj -MF CMakeFiles\PokemonBattle.dir\Pokemon.cpp.obj.d -o CMakeFiles\PokemonBattle.dir\Pokemon.cpp.obj -c "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Pokemon.cpp"

CMakeFiles/PokemonBattle.dir/Pokemon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PokemonBattle.dir/Pokemon.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Pokemon.cpp" > CMakeFiles\PokemonBattle.dir\Pokemon.cpp.i

CMakeFiles/PokemonBattle.dir/Pokemon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PokemonBattle.dir/Pokemon.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Pokemon.cpp" -o CMakeFiles\PokemonBattle.dir\Pokemon.cpp.s

CMakeFiles/PokemonBattle.dir/Moves.cpp.obj: CMakeFiles/PokemonBattle.dir/flags.make
CMakeFiles/PokemonBattle.dir/Moves.cpp.obj: ../Moves.cpp
CMakeFiles/PokemonBattle.dir/Moves.cpp.obj: CMakeFiles/PokemonBattle.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PokemonBattle.dir/Moves.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/PokemonBattle.dir/Moves.cpp.obj -MF CMakeFiles\PokemonBattle.dir\Moves.cpp.obj.d -o CMakeFiles\PokemonBattle.dir\Moves.cpp.obj -c "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Moves.cpp"

CMakeFiles/PokemonBattle.dir/Moves.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PokemonBattle.dir/Moves.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Moves.cpp" > CMakeFiles\PokemonBattle.dir\Moves.cpp.i

CMakeFiles/PokemonBattle.dir/Moves.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PokemonBattle.dir/Moves.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\Moves.cpp" -o CMakeFiles\PokemonBattle.dir\Moves.cpp.s

# Object files for target PokemonBattle
PokemonBattle_OBJECTS = \
"CMakeFiles/PokemonBattle.dir/main.cpp.obj" \
"CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj" \
"CMakeFiles/PokemonBattle.dir/Moves.cpp.obj"

# External object files for target PokemonBattle
PokemonBattle_EXTERNAL_OBJECTS =

PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/main.cpp.obj
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/Pokemon.cpp.obj
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/Moves.cpp.obj
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/build.make
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/linklibs.rsp
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/objects1.rsp
PokemonBattle.exe: CMakeFiles/PokemonBattle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable PokemonBattle.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\PokemonBattle.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PokemonBattle.dir/build: PokemonBattle.exe
.PHONY : CMakeFiles/PokemonBattle.dir/build

CMakeFiles/PokemonBattle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PokemonBattle.dir\cmake_clean.cmake
.PHONY : CMakeFiles/PokemonBattle.dir/clean

CMakeFiles/PokemonBattle.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle" "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle" "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug" "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug" "C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\cmake-build-debug\CMakeFiles\PokemonBattle.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/PokemonBattle.dir/depend

