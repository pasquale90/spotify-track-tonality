cmake_minimum_required(VERSION 3.10)
project(spotify-track-tonality)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pedantic -Wall -Wextra -Wno-error")

set(LIBRARIES
    jsoncpp
    curl
)

set (SOURCES_1
    src/main.cpp
    src/spotifeye.cpp
    # src/Error.cpp
)

set (SOURCES_2
    src/spotifeye.cpp
    src/authorize.cpp
    # src/Error.cpp
)

set(INCLUDE_DIRECTORIES
    include
)

add_executable(getCurrentTone ${SOURCES_1})
target_include_directories(getCurrentTone PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(getCurrentTone ${LIBRARIES})

add_executable(authorizeUser ${SOURCES_2})
target_include_directories(authorizeUser PRIVATE ${INCLUDE_DIRECTORIES})
target_link_libraries(authorizeUser ${LIBRARIES})