cmake_minimum_required(VERSION 3.5)
project(libdsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

aux_source_directory(. SRCS)
add_library(libdsh ${SRCS})
target_link_libraries(libdsh)
