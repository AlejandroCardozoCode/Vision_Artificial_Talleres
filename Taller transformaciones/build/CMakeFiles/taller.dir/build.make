# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build"

# Include any dependencies generated for this target.
include CMakeFiles/taller.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/taller.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/taller.dir/flags.make

CMakeFiles/taller.dir/main.cxx.o: CMakeFiles/taller.dir/flags.make
CMakeFiles/taller.dir/main.cxx.o: ../main.cxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/taller.dir/main.cxx.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/taller.dir/main.cxx.o -c "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/main.cxx"

CMakeFiles/taller.dir/main.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/taller.dir/main.cxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/main.cxx" > CMakeFiles/taller.dir/main.cxx.i

CMakeFiles/taller.dir/main.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/taller.dir/main.cxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/main.cxx" -o CMakeFiles/taller.dir/main.cxx.s

# Object files for target taller
taller_OBJECTS = \
"CMakeFiles/taller.dir/main.cxx.o"

# External object files for target taller
taller_EXTERNAL_OBJECTS =

taller: CMakeFiles/taller.dir/main.cxx.o
taller: CMakeFiles/taller.dir/build.make
taller: /usr/local/lib/libopencv_gapi.so.4.5.1
taller: /usr/local/lib/libopencv_highgui.so.4.5.1
taller: /usr/local/lib/libopencv_ml.so.4.5.1
taller: /usr/local/lib/libopencv_objdetect.so.4.5.1
taller: /usr/local/lib/libopencv_photo.so.4.5.1
taller: /usr/local/lib/libopencv_stitching.so.4.5.1
taller: /usr/local/lib/libopencv_video.so.4.5.1
taller: /usr/local/lib/libopencv_videoio.so.4.5.1
taller: /usr/local/lib/libopencv_dnn.so.4.5.1
taller: /usr/local/lib/libopencv_imgcodecs.so.4.5.1
taller: /usr/local/lib/libopencv_calib3d.so.4.5.1
taller: /usr/local/lib/libopencv_features2d.so.4.5.1
taller: /usr/local/lib/libopencv_flann.so.4.5.1
taller: /usr/local/lib/libopencv_imgproc.so.4.5.1
taller: /usr/local/lib/libopencv_core.so.4.5.1
taller: CMakeFiles/taller.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable taller"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/taller.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/taller.dir/build: taller

.PHONY : CMakeFiles/taller.dir/build

CMakeFiles/taller.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/taller.dir/cmake_clean.cmake
.PHONY : CMakeFiles/taller.dir/clean

CMakeFiles/taller.dir/depend:
	cd "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones" "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones" "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build" "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build" "/mnt/c/Users/Aleja/OneDrive/carpetas semestre/Vision Artificial/Vision_Artificial/Taller transformaciones/build/CMakeFiles/taller.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/taller.dir/depend

