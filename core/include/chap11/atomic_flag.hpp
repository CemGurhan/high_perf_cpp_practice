#include <atomic>

// atomic flags are always lock free.

class SimpleMutex {
    std::atomic_flag is_locked{};

    public:
        auto lock() noexcept {
            // test and set always sets the flag to true and also returns 
            // the previous state of the flag. If it returns false,
            // it means the caller managed to acquire the lock and set the value
            // to true (as the previous value, false, is returned).
            while (is_locked.test_and_set()) {

                // We perform a spinning check in here to avoid invalidating the 
                // cache line. When we call test, we simply hold the thread up until 
                // a thread calls unlock and the value of the flag is set to false.
                while (is_locked.test());
            }
        }

        auto unlock() noexcept {
            is_locked.clear(); //s ets flag to false
        }
};

// the issue with the example above is the thread keeps spinning and can 
// keep the CPU constantly active.
// this pattern above is known as "test and test-and-set".

 // A better method is to call `wait` on the atomic flag. This will block until
 // the value of the atomic flag has changed from what was passed in, resulting in no CPU burn from constantly 
 // re-polling. 

 class SimpleMutexEfficient {
    std::atomic_flag is_locked{};

    public:
        auto lock() noexcept {
            while (is_locked.test_and_set()) {
                is_locked.wait(true); // blocks here until flag value changes from true -> false
            }
        }

        auto unlock() noexcept {
            is_locked.clear();
        }
 };
