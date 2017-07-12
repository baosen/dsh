#pragma once
#include "kb.hpp"

// Keyboard subsystem for file system.
namespace kbsys {
    // Initialize keyboard subsystem.
    void init();
    // Deinitialize keyboard subsystem.
    void deinit();

    // Get next keyboard event.
    input_event get();
}
