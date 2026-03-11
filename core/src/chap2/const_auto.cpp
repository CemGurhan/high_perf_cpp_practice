#include <iostream>

using std::vector;

vector<int> get_prices() {
    vector<int> v = {100, 101, 102};
    return v;
}

void vector_lifetime_extension() {
    // const auto can be used to extend the lifetime of a temporary object returned by a function.
    // If we were to do this, the compiler would fail:
    // auto& data = get_prices();
    // as we'd be trying to take a mutable reference to something that is a temporary and will be destroyed after the return.

    // We can do this. Due to copy elision in C++ 17, the vector returned by get_prices is constructed directly in vCopy, 
    // so it has its own lifetime and can be used safely. The vector is not created and discarded in get_prices, it is constructed directly in vCopy.
   [[maybe_unused]] auto vLifetime = get_prices(); 

    // The const auto& allows us to promise the compiler we won't modify the data,
    // allowing us to extend its lifetime past the return of get_prices. The fact that
    // it's a const reference means we avoid copying the vector, and we can safely use it as long as we don't modify it.
    [[maybe_unused]] const auto& vConst = get_prices();

    // This doesn't actually move data at all. vConst is a const reference so it cannot be moved from. 
    // Instead, this will just create a copy of the vector in vConst.
    vLifetime = std::move(vConst);
    vLifetime[0] = 1;
}
