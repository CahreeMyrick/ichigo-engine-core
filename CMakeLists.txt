cmake_minimum_required(VERSION 3.20)

# Project declaration
project(ICHIGO
    VERSION 0.1.0
    LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Debug if user doesn't specify
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Extra debug info + nicer warnings for Clang/GCC
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(
        -g              # debug symbols (LLDB likes this)
        -O0             # no optimization, easier debugging
        -Wall -Wextra
        -Wpedantic
    )
endif()

# Where headers live
include_directories(${CMAKE_SOURCE_DIR}/include)

# ---- Engine core library ----
add_library(chess
    src/board.cpp
    src/piece.cpp
    src/game.cpp
)

# ---- Main executable ----
add_executable(ichigo
    src/main.cpp
)
target_link_libraries(ichigo PRIVATE chess)

add_executable(chess_tests tests/test.cpp)
target_link_libraries(chess_tests PRIVATE chess)

