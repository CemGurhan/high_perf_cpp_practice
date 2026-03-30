#include <memory>
#include <thread>

void shared_pointer_locked() {

    // control blocks on shared pointers are thread safe by default.
    // The actual memory they point to (in this case an int) are not thread
    // safe by default, so a locking mechanism must be implemented. 
    auto p1 = std::make_shared<int>(42);

    // capture p1 by value, they own their data so p2 will still cause the
    // control block to update. If done by ref, p1 getting destroyed would cause p2 
    // to have a dangling reference.
    auto t = std::jthread([p1] ()  {
        // The control block is thread safe, so the 
        // reference count is updated correctly.
        auto p2 = p1; 
    });
}


