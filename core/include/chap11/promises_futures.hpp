#include <thread>
#include <iostream>
#include <future>      // std::promise, std::future

auto divide(int a, int b, std::promise<int>& p) {
    if (b == 0) {
        auto e = std::runtime_error{"Divide by zero exception"};
        // set exception requires an exception ptr
        p.set_exception(std::make_exception_ptr(e));
    } else {
        const auto result = a / b;
        p.set_value(result);
    }
}

void run_divide_w_promise() {
    auto p = std::promise<int>{};
    // we must pass a ref to promise so that the two functions 
    // don't get separate copies. They need a shared promise.
    std::jthread(divide, 45, 5, std::ref(p)); 

    auto f = p.get_future();
    try {
        const auto& result = f.get(); //blocks until ready
        std::cout << "Result: " << result << '\n';
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << '\n';
    }
}

