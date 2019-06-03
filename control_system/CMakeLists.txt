# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (motor)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-files)

find_package(SystemC REQUIRED)
find_package(SystemCAMS REQUIRED)

include_directories(${SYSTEMC_INCLUDE_DIRS}  
                    ${SYSTEMCAMS_INCLUDE_DIRS}) 

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
    src/dc_motor.cpp
    src/pid_controller.cpp
	 src/pwm_modulator.cpp
)

# Add an executable with the above sources
add_executable(motor ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(motor
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(motor 
	${SYSTEMC_LIBRARIES}
	${SYSTEMCAMS_LIBRARIES}
)