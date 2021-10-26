cmake_minimum_required(VERSION 3.21)
project(nyckel)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_executable(nyckeld
    src/main.cpp src/Storage.cpp
    )
target_include_directories(nyckeld PRIVATE include)

# Library
add_subdirectory(libnyckel)
target_link_libraries(nyckeld nyckel)