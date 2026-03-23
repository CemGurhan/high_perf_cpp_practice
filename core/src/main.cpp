
#include <iostream>
#include <vector>
#include "chap2/auto.hpp"
#include "chap2/const_auto.hpp"
#include "chap2/forwarding_auto.hpp"
#include <thread>
#include <chap2/lambdas_capture.hpp>
#include "chap2/call_operator.hpp"
#include "chap4/vectors_resize_and_stackvsheapalloc.hpp"
#include "chap4/basic_string.hpp"
#include "chap4/priority_queues.hpp"
#include "chap11/thread_join.hpp"
#include "chap11/jthreads.hpp"
#include "chap11/mutex.hpp"
#include "chap11/promises_futures.hpp"
#include "chap11/packaged_task.hpp"
#include "chap11/async.hpp"
#include "chap11/latches.hpp"

int main() {
    // auto_ref_strip();

    // decltype_auto();

    // vector_lifetime_extension();

    // lambda_capture_copy_vs_ref();
    
    // operator_example();

    // erase_if();

    // basic_string();

    // priority_queue_least_func();

    // priority_queue_most_func();

    // run_print_thread();

    // run_jthread();

    // run_stoppable_jthread();

    // racey_count();

    // run_divide_w_promise();

    // run_divide_with_packaged_task();

    // run_divide_with_async();

    use_latches();
}

