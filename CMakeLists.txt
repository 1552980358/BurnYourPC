cmake_minimum_required(VERSION 3.19)
project(BurnYourPC)

set(CMAKE_CXX_STANDARD 20)

SET(CMAKE_CXX_FLAGS "-pthread -static")

option(MINGW_STDTHREADS_GENERATE_STDHEADERS "" ON)

include_directories("ExtLibs\\boost_1_76_0")
include_directories("ExtLibs\\OpenCL-ICD-Loader\\inc")
include_directories("ExtLibs\\mingw-std-threads")

link_directories("ExtLibs\\OpenCL-ICD-Loader\\out\\install\\x64-Debug\\lib")
link_libraries(OpenCL.lib)

add_executable(BurnYourPC
        main.cpp
        Burner.cpp Burner.h
        CPUBurner.cpp CPUBurner.h
        utils.cpp utils.h
        GPUBurner.cpp GPUBurner.h
        gpu_burner/GPUBurnerTask.cpp gpu_burner/GPUBurnerTask.h
        gpu_burner/GPUPiDoubleBurner.cpp gpu_burner/GPUPiDoubleBurner.h
        )
target_link_libraries(BurnYourPC OpenCL.lib)