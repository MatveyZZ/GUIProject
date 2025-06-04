cmake_minimum_required(VERSION 3.16)
project(GUIProject CXX)

#add_executable(gameoflife WIN32 "src/GameOfLife.cpp" "src/GameOfLife.h" "src/main.cpp")
add_executable(gameoflife WIN32 "src/main.cpp")

target_include_directories(gameoflife PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries(gameoflife "${CMAKE_SOURCE_DIR}/lib/x64/SDL2main.lib")
target_link_libraries(gameoflife "${CMAKE_SOURCE_DIR}/lib/x64/SDL2.lib")