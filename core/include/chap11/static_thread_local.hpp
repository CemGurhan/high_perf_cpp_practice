#include <random>

// We can use static thread_local to create a piece of static memory (memory
// that is stored in shared static memory and that exists for the duration of the programme),
// but the thread_local ensures that each thread gets its own instance of this static memory.

// Take this function that creates a random number between 1-6. The heavy random engine
// is created in static memory. Each thread will then get its own instance of this engine that they 
// can then reuse:

// // Thread 1 first call:
// static thread_local auto engine = ...;  // Create engine once
// return dist(engine);

// // Thread 1 second call:
// static thread_local auto engine = ...;  // Already exists, reuse
// return dist(engine);

// // Thread 2 first call:
// static thread_local auto engine = ...;  // Separate instance created
// return dist(engine);
auto random_int(int min, int max) {
  // One engine instance per thread
  static thread_local auto engine = 
    std::default_random_engine{std::random_device{}()}; // random device generates a seed to the engine
  auto dist = std::uniform_int_distribution<>{min, max};
  return dist(engine);
}
