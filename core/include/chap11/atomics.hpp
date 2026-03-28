#include <atomic>
#include <cassert>

void is_lock_free() {
    // atomics aren't necessarily always lock free.
    // We can check at runtime whether they are or not with the 
    // is_lock_free method:
    auto a = std::atomic<int>{1};
    assert(a.is_lock_free());
}
