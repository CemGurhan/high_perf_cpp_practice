#include <thread>
#include <iostream>
#include <latch>

// latches can be used to wait for threads to decrement a count to zero (used to block threads 
// from progressing until an invariant is met).

void some_work_for_demo_here() {
    std::cout << "im done working mate\n";
}

void use_latches() {
    auto n_threads = 2;
    auto latch = std::latch{n_threads}; 
    auto threads = std::vector<std::jthread>{};

    // queue some threads to do work, each one decrements the latch and 
    // waits for the latches to be at 0.
    for (auto i = 0; i < n_threads; ++i) { 
        threads.emplace_back([&] {
            latch.arrive_and_wait(); // calls latch.count_down() then latch.wait()
            some_work_for_demo_here();
        });
    }

    latch.wait(); // wait for the threads to decrement latch to zero.
    std::cout << "now lets do some relaxing\n";
}
