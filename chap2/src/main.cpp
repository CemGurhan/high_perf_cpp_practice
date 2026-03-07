
#include <iostream>
#include <vector>
#include "auto.hpp"
#include "const_auto.hpp"
#include "forwarding_auto.hpp"
#include <thread>

static std::thread* ts;

int main() {
    // auto_ref_strip();

    // decltype_auto();

    // vector_lifetime_extension();

    forward_vector();
}

