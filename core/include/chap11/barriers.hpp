#include <vector>
#include <thread>
#include <barrier>
#include <iostream>
#include "static_thread_local.hpp"

void dice_roll() {
    constexpr auto n = 5; // Number of dice
    auto done = false;
    auto dice = std::array<int, n>{};
    auto threads = std::vector<std::jthread>{};
    auto n_turns = 0;

    // completion function - only ran when the barrier is
    // complete. Safe to run with ref data as all threads will be
    // waiting at this point.
    auto check_result = [&] { 
        ++n_turns;
        auto is_six = [](auto i) { return i == 6; };
        done = std::all_of(dice.begin(), dice.end(), is_six);
    };

    auto bar = std::barrier{n, check_result};

    for (int i = 0; i < n; ++i) {
        threads.emplace_back([&, i] { // capture i by value so each thread gets own copy
            while (!done) {
                dice[i] = random_int(1, 6); // Roll dice        
                bar.arrive_and_wait();       // Join 
                }
            });
    }

    std::cout << "6 rolls of 6 recorded\n";
}

