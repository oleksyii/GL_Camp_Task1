# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/oleksii/GLTask1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oleksii/GLTask1/build

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/Client/Client.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Client/Client.cpp.o: /home/oleksii/GLTask1/src/Client/Client.cpp
CMakeFiles/Client.dir/Client/Client.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/Client/Client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/Client/Client.cpp.o -MF CMakeFiles/Client.dir/Client/Client.cpp.o.d -o CMakeFiles/Client.dir/Client/Client.cpp.o -c /home/oleksii/GLTask1/src/Client/Client.cpp

CMakeFiles/Client.dir/Client/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Client/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/Client/Client.cpp > CMakeFiles/Client.dir/Client/Client.cpp.i

CMakeFiles/Client.dir/Client/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Client/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/Client/Client.cpp -o CMakeFiles/Client.dir/Client/Client.cpp.s

CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o: /home/oleksii/GLTask1/src/PNet/IPEndpoint.cpp
CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o -MF CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o.d -o CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o -c /home/oleksii/GLTask1/src/PNet/IPEndpoint.cpp

CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/PNet/IPEndpoint.cpp > CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.i

CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/PNet/IPEndpoint.cpp -o CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.s

CMakeFiles/Client.dir/PNet/Network.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PNet/Network.cpp.o: /home/oleksii/GLTask1/src/PNet/Network.cpp
CMakeFiles/Client.dir/PNet/Network.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Client.dir/PNet/Network.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/PNet/Network.cpp.o -MF CMakeFiles/Client.dir/PNet/Network.cpp.o.d -o CMakeFiles/Client.dir/PNet/Network.cpp.o -c /home/oleksii/GLTask1/src/PNet/Network.cpp

CMakeFiles/Client.dir/PNet/Network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PNet/Network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/PNet/Network.cpp > CMakeFiles/Client.dir/PNet/Network.cpp.i

CMakeFiles/Client.dir/PNet/Network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PNet/Network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/PNet/Network.cpp -o CMakeFiles/Client.dir/PNet/Network.cpp.s

CMakeFiles/Client.dir/PNet/Packet.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PNet/Packet.cpp.o: /home/oleksii/GLTask1/src/PNet/Packet.cpp
CMakeFiles/Client.dir/PNet/Packet.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Client.dir/PNet/Packet.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/PNet/Packet.cpp.o -MF CMakeFiles/Client.dir/PNet/Packet.cpp.o.d -o CMakeFiles/Client.dir/PNet/Packet.cpp.o -c /home/oleksii/GLTask1/src/PNet/Packet.cpp

CMakeFiles/Client.dir/PNet/Packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PNet/Packet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/PNet/Packet.cpp > CMakeFiles/Client.dir/PNet/Packet.cpp.i

CMakeFiles/Client.dir/PNet/Packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PNet/Packet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/PNet/Packet.cpp -o CMakeFiles/Client.dir/PNet/Packet.cpp.s

CMakeFiles/Client.dir/PNet/Socket.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/PNet/Socket.cpp.o: /home/oleksii/GLTask1/src/PNet/Socket.cpp
CMakeFiles/Client.dir/PNet/Socket.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Client.dir/PNet/Socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/PNet/Socket.cpp.o -MF CMakeFiles/Client.dir/PNet/Socket.cpp.o.d -o CMakeFiles/Client.dir/PNet/Socket.cpp.o -c /home/oleksii/GLTask1/src/PNet/Socket.cpp

CMakeFiles/Client.dir/PNet/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/PNet/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/PNet/Socket.cpp > CMakeFiles/Client.dir/PNet/Socket.cpp.i

CMakeFiles/Client.dir/PNet/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/PNet/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/PNet/Socket.cpp -o CMakeFiles/Client.dir/PNet/Socket.cpp.s

CMakeFiles/Client.dir/Platform/Linux_.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Platform/Linux_.cpp.o: /home/oleksii/GLTask1/src/Platform/Linux_.cpp
CMakeFiles/Client.dir/Platform/Linux_.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Client.dir/Platform/Linux_.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/Platform/Linux_.cpp.o -MF CMakeFiles/Client.dir/Platform/Linux_.cpp.o.d -o CMakeFiles/Client.dir/Platform/Linux_.cpp.o -c /home/oleksii/GLTask1/src/Platform/Linux_.cpp

CMakeFiles/Client.dir/Platform/Linux_.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Platform/Linux_.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/Platform/Linux_.cpp > CMakeFiles/Client.dir/Platform/Linux_.cpp.i

CMakeFiles/Client.dir/Platform/Linux_.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Platform/Linux_.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/Platform/Linux_.cpp -o CMakeFiles/Client.dir/Platform/Linux_.cpp.s

CMakeFiles/Client.dir/Platform/Windows_.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/Platform/Windows_.cpp.o: /home/oleksii/GLTask1/src/Platform/Windows_.cpp
CMakeFiles/Client.dir/Platform/Windows_.cpp.o: CMakeFiles/Client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Client.dir/Platform/Windows_.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Client.dir/Platform/Windows_.cpp.o -MF CMakeFiles/Client.dir/Platform/Windows_.cpp.o.d -o CMakeFiles/Client.dir/Platform/Windows_.cpp.o -c /home/oleksii/GLTask1/src/Platform/Windows_.cpp

CMakeFiles/Client.dir/Platform/Windows_.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Platform/Windows_.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/oleksii/GLTask1/src/Platform/Windows_.cpp > CMakeFiles/Client.dir/Platform/Windows_.cpp.i

CMakeFiles/Client.dir/Platform/Windows_.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Platform/Windows_.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/oleksii/GLTask1/src/Platform/Windows_.cpp -o CMakeFiles/Client.dir/Platform/Windows_.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/Client/Client.cpp.o" \
"CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o" \
"CMakeFiles/Client.dir/PNet/Network.cpp.o" \
"CMakeFiles/Client.dir/PNet/Packet.cpp.o" \
"CMakeFiles/Client.dir/PNet/Socket.cpp.o" \
"CMakeFiles/Client.dir/Platform/Linux_.cpp.o" \
"CMakeFiles/Client.dir/Platform/Windows_.cpp.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

bin/Client: CMakeFiles/Client.dir/Client/Client.cpp.o
bin/Client: CMakeFiles/Client.dir/PNet/IPEndpoint.cpp.o
bin/Client: CMakeFiles/Client.dir/PNet/Network.cpp.o
bin/Client: CMakeFiles/Client.dir/PNet/Packet.cpp.o
bin/Client: CMakeFiles/Client.dir/PNet/Socket.cpp.o
bin/Client: CMakeFiles/Client.dir/Platform/Linux_.cpp.o
bin/Client: CMakeFiles/Client.dir/Platform/Windows_.cpp.o
bin/Client: CMakeFiles/Client.dir/build.make
bin/Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/oleksii/GLTask1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable bin/Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: bin/Client
.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/oleksii/GLTask1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oleksii/GLTask1/src /home/oleksii/GLTask1/src /home/oleksii/GLTask1/build /home/oleksii/GLTask1/build /home/oleksii/GLTask1/build/CMakeFiles/Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

