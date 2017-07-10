#pragma once
#include "kb.hpp"

// Keyboard subsystem for file system.
namespace kbsys {
    extern Kb kb;

    // Initialize keyboard subsystem.
    void init();
    // Deinitialize keyboard subsystem.
    void deinit();
}
