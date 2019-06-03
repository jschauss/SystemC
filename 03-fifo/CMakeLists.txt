# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (fifo)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-files)

find_package(SystemC REQUIRED)

include_directories(${SYSTEMC_INCLUDE_DIRS}) 

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
    src/producer_consumer.cpp
)

set (CMAKE_PREFIX_PATH /usr/local/systemc-2.3.2)

include_directories(${CMAKE_PREFIX_PATH}/include)

find_library(systemc systemc ${CMAKE_PREFIX_PATH}/lib-linux64)
link_directories(${CMAKE_PREFIX_PATH}/lib-linux64)

# Add an executable with the above sources
add_executable(fifo ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(fifo
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(fifo
	${SYSTEMC_LIBRARIES}
)