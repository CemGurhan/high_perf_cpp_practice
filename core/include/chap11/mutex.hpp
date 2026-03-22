#include <thread>
#include <iostream>
#include <cassert>

int counter = 0; 
auto counter_mu = std::mutex{};

void increment_counter(int n) {
    for (int i = 0; i < n; ++i) {
        // auto unlocks when out of scope, remove this and watch racey_count fail
        auto lock = std::scoped_lock{counter_mu}; 
        ++counter;
    }
}

void racey_count() {
    const int n = int{1'000'000};

    {
        auto t1 = std::jthread{increment_counter, n};
        auto t2 = std::jthread{increment_counter, n};
    }; // jthreads go out of scope here and auto join.

    std::cout << counter << '\n';
    assert(counter == n * 2);
}
