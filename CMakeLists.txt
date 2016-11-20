cmake_minimum_required(VERSION 3.6)
project(JSBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    music_theory.cpp)

add_executable(JSBot ${SOURCE_FILES})