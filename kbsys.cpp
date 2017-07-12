#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include "kbsys.hpp"
using namespace std;

// Keyboard subsystem for file system.
namespace {
    // User's keyboard:
    Kb                 kb;            // A handle to the keyboard itself.

    // Threads reading from both keyboard event files:
    thread             k1,            // Handling keyboard file event1.
                       k2;            // Handling keyboard file event2.
    bool               kexit = false; // Set to exit and stop the keyboard threads.

    // Shared keyboard input event queue:
    deque<input_event> ievs;          // Queue of keyboard events.
    mutex              m;             // Lock to use to make the threads share the queue together.
    condition_variable v;             // Used to notify that there is input events in the queue.
}

// Append new keyboard event to the queue.
static void append(const input_event& e)
{
    // Guard this critical section.
    unique_lock<mutex> l(m);

    // Append keyboard event.
    ievs.push_back(e);
    // Job is done, unlock so the other thread can do its job.
    l.unlock();
    // Notify that an input event has arrived.
    v.notify_one();
}

// Get next keyboard event.
input_event kbsys::get()
{
    // Guard this critical section.
    unique_lock<mutex> l(m);

    // Release lock and wait for input events.
    if (ievs.empty()) {
        v.wait(l, [] { 
            // DEBUG: Sanity check (may not be needed).
            return !ievs.empty();
        });
    }

    // Get next keyboard event.
    const auto e = ievs.front();
    ievs.pop_front();
    return e;
}

// Setup and initialize keyboard subsystem.
void kbsys::init() 
{
    // Open keyboard file.
    kb.open();

    // Setup keyboard threads.
    kexit = false;
    k1 = thread([](){
        while (!kexit) // TODO: If set, thread won't exit before user has pressed a key, because of blocking.
            append(kb.rd1()); // Blocks.
    });
    k2 = thread([](){
        while (!kexit) // TODO: If set, thread won't exit before user has pressed a key, because of blocking.
            append(kb.rd2()); // Blocks.
    });
}

// Cleanup keyboard subsystem.
void kbsys::deinit() 
{
    // Exit keyboard threads.
    kexit = true;
    k1.join(); // TODO: May get stuck because of no user input.
    k2.join(); // TODO: May get stuck because of no user input.
    // BUG: If you time pressing ENTER correctly, you may exit k2.

    // Close keyboard file.
    kb.close();
}
