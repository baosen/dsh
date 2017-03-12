project(dsh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Set source dependencies for desktop shell.
set(SRC
    btn.cpp
    col.cpp
    drm.cpp
    dsh.cpp
    fb.cpp
    ft.cpp
    kb.cpp
    log.cpp
    mouse.cpp
    open.cpp
    path.cpp
    pos.cpp
    rect.cpp
    res.cpp
    scr.cpp
    wnd.cpp
)

# Compile desktop shell executable.
add_executable(dsh dsh.cpp ${SRC})