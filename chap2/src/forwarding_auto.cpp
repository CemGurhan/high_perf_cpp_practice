#include <iostream>
#include "const_auto.hpp"

using std::vector;
using std::cout;

void forward_vector() {
    [[maybe_unused]] auto&& v = forward_out();
    v[0] = 997; // forwarded again so can edit.
}

std::vector<int> forward_out() {
    // auto&& is a forwarding reference, it is used to extend
    // the lifetime of a temporary object and to perfectly forward it.
    // The forwarded object can be mutated.
    auto&& v = get_prices(); 

    const auto& vConst = get_prices();

    cout << "before:" << "\n";
    for (const auto& price : v) {
        cout << price << " ";
    }
    cout << "\n";

    v[0] = 998;
    // vConst[0] = 999; // this will not compile, as vConst is a const reference and cannot be modified

    cout << "after:" << "\n";
    for (const auto& price : v) {
        cout << price << " ";
    }
    cout << "\n";

    return vConst; 
}
