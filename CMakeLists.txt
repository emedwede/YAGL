cmake_minimum_required(VERSION 3.9)

# set the project name and version
project(YAGL VERSION 0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_subdirectory(tests)
