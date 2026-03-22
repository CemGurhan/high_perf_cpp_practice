#include <thread>
#include <iostream>

auto cv = std::condition_variable{}; 
auto q = std::queue<int>{}; 
auto mtx = std::mutex{};     // Protects the shared queue 
constexpr int sentinel = -1; // Value to signal that we are done 
 
void print_ints() { 
  auto i = 0; 
  while (i != sentinel) { 
    { 
      auto lock = std::unique_lock<std::mutex>{mtx}; 
      // while loop on q empty because of spurious wake ups. 
      // The cv could be awakened for any reason that's unrelated to
      // the producer consumer pattern (e.g OS interrupt).
      // At this point the queue might still be empty, so we need
      // to check here jsut incase. If we didn't, q.front would fail.
      // Another consumer could have also awakened and emptied the queue before
      // us. When the release the lock, we might acquire before the producer had a chance to push,
      // so we must also check for empty queue here too.
      while (q.empty()) {
        // When we reach here, we wait for the producer to 
        // run notify_one. The lock is released whilst we wait
        // and is re-acquired as soon as we're out.
        cv.wait(lock); // condition variables wait expects a unique lock
        // lock re-acquired here
      }
      i = q.front(); // we have lock here
      q.pop(); // we have lock here
    } 

    if (i != sentinel) { 
      std::cout << "Got: " << i << '\n'; 
    } 
  } 
} 
 
auto generate_ints() { 
  for (auto i : {1, 2, 3, sentinel}) { 
    std::this_thread::sleep_for(std::chrono::seconds(1)); 

    { 
    // producer blocked here whenever consumer has lock (whenever consumer is out of wait block)
      auto lock = std::scoped_lock{mtx}; 
      q.push(i); 
    } 

    cv.notify_one(); 
  } 
} 
  
int main() { 
   auto producer = std::jthread{generate_ints}; 
   auto consumer = std::jthread{print_ints}; 
}
