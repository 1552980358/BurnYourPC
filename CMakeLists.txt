cmake_minimum_required(VERSION 3.19)
project(BurnYourPC)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS -pthread)

option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)

include_directories("ExtLibs\\boost_1_76_0")
include_directories("ExtLibs\\OpenCL-ICD-Loader\\inc")
include_directories("ExtLibs\\mingw-std-threads")

link_directories("ExtLibs\\OpenCL-ICD-Loader\\out\\install\\x64-Debug\\bin")
link_libraries(OpenCL.dll)

add_executable(BurnYourPC main.cpp Burner.h Burner.cpp CPUBurner.cpp CPUBurner.h utils.cpp utils.h GPUBurner.cpp GPUBurner.h gpu_burner/GPUBurnerTask.cpp gpu_burner/GPUBurnerTask.h)
target_link_libraries(BurnYourPC OpenCL.dll)