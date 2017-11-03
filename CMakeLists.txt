cmake_minimum_required(VERSION 3.6)
project(OS_Group_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Utility.cpp src/PCB.cpp src/Disk.cpp src/Loader.cpp src/Log.cpp src/termcolor.hpp)

add_executable(MyTarget ${SOURCE_FILES})
