cmake_minimum_required(VERSION 3.6)
project(OS_Group_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/utility.cpp src/Ram.cpp src/PCB.cpp src/Loader.cpp src/Driver.cpp src/Disk.cpp src/CPU.cpp src/Scheduler.h src/Scheduler.cpp src/Log.cpp)
add_executable(MyTarget ${SOURCE_FILES})
