
#include <iostream>
#include <vector>
#include "chap2/auto.hpp"
#include "chap2/const_auto.hpp"
#include "chap2/forwarding_auto.hpp"
#include <thread>
#include <chap2/lambdas_capture.hpp>
#include "chap2/call_operator.hpp"
#include "chap4/vectors_resize_and_stackvsheapalloc.hpp"

int main() {
    // auto_ref_strip();

    // decltype_auto();

    // vector_lifetime_extension();

    // lambda_capture_copy_vs_ref();
    
    operator_example();

    erase_if();
}

