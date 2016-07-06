cmake_minimum_required(VERSION 3.5)
project(dsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(libdsh)
add_executable(dsh dsh.cpp)
target_link_libraries(dsh libdsh)

add_subdirectory(libdsh)
