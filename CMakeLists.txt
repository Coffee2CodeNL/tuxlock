cmake_minimum_required(VERSION 3.10)
project(TuxLock)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-modules/")

option(DEBUG_BUILD "Sets debug mode" On)

# Packages
find_package(Threads)
find_package(LIBPARTED)
# Includes
set(tuxlock_INCLUDES
        lib/cxxopts/include
        lib/rang/include
        lib/spdlog/include
        #        lib/parted-3.2/include
        )
include_directories(${tuxlock_INCLUDES})
# tuxlock-cli executable
set(NAME_TUXLOCK_CLI_EXEC "tuxlock-cli")
add_definitions(-DTUXLOCK_CLI_EXEC_NAME=${NAME_TUXLOCK_CLI_EXEC})
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    message("-- Setting debug mode")
    add_definitions(-DTL_DEBUG)
endif (CMAKE_BUILD_TYPE MATCHES "Debug")
set(tuxlock-cli_SOURCES
        ${BACKWARD_ENABLE}
        src/TuxLock.cpp
        src/TuxLock.hpp
        src/Drive/Generic.cpp
        src/Drive/Generic.hpp
        src/CLI/CLI.cpp
        src/CLI/CLI.hpp src/Drive/NVMe.cpp src/Drive/NVMe.hpp)
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/backward-cpp")
add_executable(${NAME_TUXLOCK_CLI_EXEC} ${tuxlock-cli_SOURCES})
add_backward(${NAME_TUXLOCK_CLI_EXEC})
target_link_libraries(${NAME_TUXLOCK_CLI_EXEC} ${CMAKE_THREAD_LIBS_INIT} ${LIBPARTED_LIBS})