cmake_minimum_required (VERSION 2.6)
project(terrain)

include_directories(src/libs/sfml/include)

set(EXECUTABLE_OUTPUT_PATH build)
set(LIBRARY_OUTPUT_PATH build)


add_executable(terrain src/main.cpp)
