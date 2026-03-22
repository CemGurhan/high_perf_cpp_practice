#include <thread>
#include <iostream>
using std::cout;

// With jthreads, we don;t have to call 'join' before destruction.
// This means we don't have to worry about termination of programme 
// when they're destructed.
// We can also pass in stopping tokens to forcibly stop thread processes.

void print_jthread() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "Internal JThread: " << std::this_thread::get_id() << '\n';
}

void run_jthread() {
    cout << "Main Thread 1" << std::this_thread::get_id() << "\n";
    auto jThread1 = std::jthread{print_jthread};
    cout << "Main Thread END" << '\n';
} // j thread will go out of scope and auto join.

void print_jthread_with_stop(std::stop_token stop) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while (!stop.stop_requested()) {
        cout << "Internal Thread: " << std::this_thread::get_id() << '\n';
    }

    cout << "Stop Requested" << '\n';
}

void run_stoppable_jthread() {
    auto jThread1 = std::jthread{print_jthread_with_stop};
    cout << "main thread sleeping" << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << "main thread requesting thread to stop\n";

    jThread1.request_stop(); // Even if we didn't call this, the destruction of the jthread would cause this.
}
