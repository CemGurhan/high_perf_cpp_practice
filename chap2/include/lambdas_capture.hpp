#include <vector>
#include <iostream>
#include <list>

using std::cout;
using std::endl;

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

void initialise_lambda_members() {
    auto init_vec = [nums = std::list<int>{4,2}]() { // init a linked list for this lambda class
        for (auto i : nums)
            cout << i << "\n"; // prints 4 and 2
    };


    init_vec();
}

void mutable_lambdas() {
     auto mutable_members = [count=1]() mutable { // can only mutate members if mutable
        cout << count << "\n"; // prints 1
        count++;
        cout << count << "\n"; // prints 2
     };

     mutable_members();

     auto v = 8;

     auto mutable_refs = [&v]() { // captured references are mutable by default, so we can modify v without mutable
        cout << v << "\n"; // prints 8
        v++;
        cout << v << "\n"; // prints 9
     };
     mutable_refs();

     auto mutable_copies = [v]() mutable { // captured by value, so we need mutable to modify the copy of v
        cout << v << "\n"; // prints 8
        v++;
        cout << v << "\n"; // prints 9
     };

    mutable_copies();
 }


 void capture_wildcards() {
    auto a = 0;
    auto b = 1;
    auto c = 2;

    auto capture_all_by_copy = [=]() { cout << a << b << c; }; // all variables ( a b and c) captured are copies
    auto capture_all_by_ref = [&]() { cout << a << b << c; }; // all variables captured are references
    auto mix_capture = [=, &c]() { cout << a << b << c; }; // capture a and b by copy, and c by reference
 }

 void default_lambda_construction() {
    // lambdas can be constructed using decltype if there are no closures.
    // This is because the compiler can find the blueprint of the original lambda
    // and reuse it. If the lambda has closures, the compiler wont know where to get the
    // enclosed variables, so it cannot default construct.

    auto a = [](int i) { cout << i << endl; };
    auto b = a;
    decltype(a) z; // z is default constructed

    static_assert(std::is_same_v<decltype(z), decltype(b)>);
 }
