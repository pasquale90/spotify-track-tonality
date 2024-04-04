cmake_minimum_required(VERSION 3.10)
project(spotify-track-tonality)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pedantic -Wall -Wextra -Wno-error")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_executable(getCurrentTone main.cpp)
target_include_directories(getCurrentTone PRIVATE ${PYTHON_LIBRARIES})
target_link_libraries(getCurrentTone ${PYTHON_LIBRARIES})