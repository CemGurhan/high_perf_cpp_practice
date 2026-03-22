#include <iostream>

// We can use async to avoid creating expensive threads all the time.


void run_divide_with_async() {
    auto f = std::async(divide_throw, 45, 5);

    try {
        auto result = f.get();
        std::cout << "Result (async): " << result << '\n';
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}
