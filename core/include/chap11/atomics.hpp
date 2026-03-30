#include <atomic>
#include <cassert>

void is_lock_free() {
    // atomics aren't necessarily always lock free.
    // We can check at runtime whether they are or not with the 
    // is_lock_free method:
    auto a = std::atomic<int>{1};
    assert(a.is_lock_free());

    // it's better to deduce whether an atomic is lock free at
    // compile time instead of runtime. In this instance, we can use
    // is_always_loc_free:

    // This won't compile if this isn't lock free.
    static_assert(std::atomic<int>::is_always_lock_free);
}
