// static local variables are shared between all threads. They are stored in
// stack memory, which is accessible by all threads. If one thread changes the 
// value of a static local variable, all threads see this change.

void func() {
    static int x = 5;  // Static memory, shared by all threads
    // All threads share the same x
}

// ```

// **Memory layout:**
// ```
// Thread 1 Stack    Thread 2 Stack    Static Memory    Heap
// [local vars]      [local vars]      [static vars]    [malloc/new]
// [x = 5]           [x = 5]           [static x = 5]   [...]
// Separate copy     Separate copy     ONE shared copy   Shared
