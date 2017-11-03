cmake_minimum_required(VERSION 3.6)
project(OS_Group_Project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

<<<<<<< HEAD
set(SOURCE_FILES src/main.cpp src/Utility.cpp src/PCB.cpp src/Disk.cpp src/Loader.cpp src/Log.cpp src/termcolor.hpp)
=======
set(SOURCE_FILES src/main.cpp src/Utility.cpp src/Ram.cpp src/PCB.cpp src/Loader.cpp src/Dispatcher.cpp src/Disk.cpp src/CPU.cpp src/Scheduler.h src/Scheduler.cpp src/Log.cpp src/termcolor.hpp src/Cache.cpp)
>>>>>>> 214ef6a702903e0c34e041e8e5d89a4f550c3fb6

add_executable(MyTarget ${SOURCE_FILES})
