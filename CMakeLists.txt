cmake_minimum_required(VERSION 3.31.0)
project(RunPsScript
    VERSION 1.0.0
    LANGUAGES CXX
)

#############################
set(CMAKE_CXX_STANDARD 23)
set(SOURCES
    RunPsScript.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    add_executable(RunPsScript ${SOURCES})
else()
    #set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")  # For /MT
    add_executable(RunPsScript WIN32 ${SOURCES})
endif()