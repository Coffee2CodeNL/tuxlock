cmake_minimum_required(VERSION 3.10)
project(tuxlock)

set(CMAKE_CXX_STANDARD 17)
set(tuxlock_INCLUDES
        lib/cxxopts/include
        lib/rang/include)
include_directories(${tuxlock_INCLUDES})
set(tuxlock-cli_SOURCES
        src/Drive/Generic.cpp
        src/Drive/Generic.h
        src/TuxlockCLI.cpp
        src/TuxlockCLI.h)
add_executable(tuxlock-cli ${tuxlock-cli_SOURCES})
