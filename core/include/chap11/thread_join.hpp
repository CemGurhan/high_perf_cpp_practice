
#include <thread>
#include <iostream>

using std::cout;


void print_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Thread ID internal: " << std::this_thread::get_id() << '\n';
}

// std::join is sued to wait for a thread to complete. 
// I fnot called, the thread will terminate the programme on
// destruction.
void run_print_thread() {
    auto t = std::thread(print_thread);
    t.join();
    std::cout << "Thread ID external: " << std::this_thread::get_id() << '\n';
}
