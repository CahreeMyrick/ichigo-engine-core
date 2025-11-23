cmake_minimum_required(VERSION 3.20)
project(ICHIGO LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED ON)

# library
add_library(chess
  src/piece.cpp
  src/board.cpp
)

target_include_directories(chess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(ichigo_main src/main.cpp)
target_link_libraries(ichigo_main PRIVATE chess)

