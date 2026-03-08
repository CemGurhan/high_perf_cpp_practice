#include <vector>
#include <iostream>

using std::cout;

void lambda_capture_copy_vs_ref() {
    auto x = 3;

    auto is_above = [x](int i) { return i > x; }; // capture x by value (copy)
    auto is_above_ref = [&x](int i) { return i > x; }; // capture x by reference

    auto v = std::vector<int>{1,2,3,4,5,6};

    x = 4;

    auto count1 = std::count_if(v.begin(), v.end(), is_above); // returns 3, as x was captured by value, so the lambda has its own copy of x which is still 3
    auto count2 = std::count_if(v.begin(), v.end(), is_above_ref); // returns 2, as x was captured by reference, so the lambda sees the updated value of x

    cout << "Count for copied: " << count1 << "\n"; // prints 3
    cout << "Count for ref: " << count2 << "\n"; // prints 2
}
