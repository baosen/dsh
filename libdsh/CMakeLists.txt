cmake_minimum_required(VERSION 3.5)
project(libdsh)

aux_source_directory(. SRCS)

add_library(libdsh ${SRCS})
target_link_libraries(libdsh)
