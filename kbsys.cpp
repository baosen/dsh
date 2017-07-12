#include <thread>
#include <deque>
#include <mutex>
#include "kbsys.hpp"
using namespace std;

// TODO: Keyboard subsystem for file system.
namespace {
    Kb                 kb;            // A handle to the keyboard itself.

    thread             k1,            // Handling keyboard file event1.
                       k2;            // Handling keyboard file event2.
    bool               kexit = false; // Set to exit and stop the keyboard threads.

    deque<input_event> ievs;          // Queue of keyboard events.
    mutex              m;             // Lock to use to make the threads share the queue together.
}

// Append new keyboard event to the queue.
static void append(const input_event& e)
{
    // TODO: LOCK!
    m.lock();

    ievs.push_back(e);
}

// Get next keyboard event.
input_event get()
{
    // TODO: LOCK!
    m.lock();
    
    // Get next keyboard event.
    const auto e = ievs.front();
    ievs.pop_front();
    return e;
}

// Setup and initialize keyboard.
void kbsys::init() 
{
    // Open keyboard file.
    kb.open();

    // Setup keyboard threads.
    k1 = thread([](){
        while (!kexit) // TODO: Potential race that can be ignored.
            append(kb.rd1());
    });
    k2 = thread([](){
        while (!kexit) // TODO: Potential race that can be ignored.
            append(kb.rd2());
    });
}

// Cleanup keyboard subsystem.
void kbsys::deinit() 
{
    // Exit keyboard threads.
    kexit = true;
    // Close keyboard file.
    kb.close();
}
