#include <semaphore>

// A semaphore allows you to restrict a critical section to X threads, as opposed to a mutex 
// which locks off the critical section for all but 1 thread.

// A semaphore is usually initialised with a particular value. Every time the semaphore is reached, 
// that value is decremented. The semaphore will then block when the value 0 is reached. This usually 
// means the maximum number of threads are now in the critical section. 

// The semaphore must be released by a thread once that thread leaves the critical section. Releasing 
// increases the number on the semaphore by 1, this is a non-blocking operation.

void run_with_counting_semaphore() {
    auto sem = std::counting_semaphore{4};

    sem.acquire();// decrement the semaphore (blocks when 0)
    // do some work - only 4 threads allowed at once
    sem.release(); // increment the semaphore

    // try acquire for 4 seconds (wait 4 seconds for the semaphore to be 
    // incremented from 0).
    sem.try_acquire_for(std::chrono::seconds(4)); 

    sem.release();
}

// a binary semaphore is one that can only increment up to 1.
// This only allows one thread access at a time. It is different from a mutex as other threads can 
// unlock this critical section, whereas with a mutex the thread that it’s locked for is the only one 
// that can unlock it.
void run_with_binary_semaphore() {
    auto b_sem = std::binary_semaphore{1};
}
