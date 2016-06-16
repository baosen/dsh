cmake_minimum_required(VERSION 3.5)
project(dshell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    button.cpp
    button.hpp
    dshell.cpp
    framebuffer.cpp
    framebuffer.hpp
    freetype.cpp
    freetype.hpp
    keyboard.cpp
    keyboard.hpp
    log.cpp
    log.hpp
    obs.cpp
    obs.hpp
    open.cpp
    wnd.cpp
    taskb.cpp
    taskb.hpp
    test.cpp
    types.hpp
    wgt.cpp
    wgt.hpp
    wnd.hpp window.cpp)

add_executable(dshell ${SOURCE_FILES})