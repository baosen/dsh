cmake_minimum_required(VERSION 3.5)
project(dsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_subdirectory(libdsh)

include_directories(libdsh)
add_executable(dsh dsh.cpp)
add_executable(mtest mtest.cpp)
target_link_libraries(dsh libdsh)
target_link_libraries(mtest libdsh)
