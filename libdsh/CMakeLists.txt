cmake_minimum_required(VERSION 3.5)
project(libdsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_executable(dsh dsh.cpp)
target_link_libraries(libdsh)
