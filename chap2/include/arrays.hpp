#include <array>

// Arrays are non-dynamic versions of vectors that have data that
// lives on the stack.
void arrays_are_unique() {
    // arrays initialized by specific size and type are unique

    auto a = std::array<int, 200>{};
    auto b = std::array<int, 3000>{};

    auto only_accepts_b = [](std::array<int, 3000> arr) {};

    only_accepts_b(b);
    // only_accepts_b(a); won't compile as a and b are not the same type

    // When an array loses its size information, it's known as array decay
}
