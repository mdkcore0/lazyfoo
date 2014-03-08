cmake_minimum_required(VERSION 2.8)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

ADD_DEFINITIONS(
    -Werror
    -Wall
    -std=c++11
)

project(lesson05)

add_subdirectory(src)
