#include <future>
#include <iostream>

// packaged tasks are a lot more succinct for obtaining futures than working with promises.

int divide_throw(int a, int b) {
    if (b == 0) {
        throw std::runtime_error{"Divide by zero exception"};
    }

    return a / b;
}

void run_divide_with_packaged_task() {
    auto task = std::packaged_task<decltype(divide_throw)>{divide_throw};
    auto f = task.get_future();
    std::jthread{std::move(task), 45, 5};

    try {
        auto result = f.get();
        std::cout << "Result (packaged): " << result << '\n';
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}
