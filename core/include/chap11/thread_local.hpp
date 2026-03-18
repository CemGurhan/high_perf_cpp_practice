thread_local int counter;

// any thread that now increments this counter will have its
// own copy of counter, given we marked counter as thread_local.
void increment_counter() {
    ++counter;
}

// Thread 1 calls increment()
// Thread 1's counter becomes 1

// Thread 2 calls increment()
// Thread 2's counter becomes 1 (separate instance)

// counter in Thread 1 is still 1
// counter in Thread 2 is 1
