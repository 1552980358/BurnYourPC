cmake_minimum_required(VERSION 3.19)
project(BurnYourPC)

set(CMAKE_CXX_STANDARD 20)

include_directories("ExtLibs\\boost_1_76_0")
include_directories("ExtLibs\\OpenCL-ICD-Loader\\inc")
link_directories("ExtLibs\\OpenCL-ICD-Loader\\out\\install\\x64-Debug\\bin")
link_libraries(OpenCL.dll)

add_executable(BurnYourPC main.cpp Burner.h CPUBurner.cpp CPUBurner.h utils.cpp utils.h)
target_link_libraries(BurnYourPC OpenCL.dll)