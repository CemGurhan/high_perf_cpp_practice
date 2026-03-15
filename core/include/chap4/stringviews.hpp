#include <string>

void string_views() {
    // string views point to a slice of an std::string.
    // They are non-owning reference types, meaning they do not own
    // the underlying memory they point to (the std::string will).

    auto sOwned = std::string{"HelloMatey"};

    auto sViewWhole = std::string_view{sOwned}; 

    // data returns pointer, we add 5 to get 5 spaces past start
    auto sViewPartial = std::string_view{sOwned.data() + 5, 5}; // Matey

}

// CStyle strings must be null terminated as they dont store length information, so we use the null 
// termination to know where they end. Std::string does have length information, but is null terminated 
// for backwards compatibility with c style strings.
// string_view does not need a null termination, so taking substr of a string view is more efficient as
// a new string does not need to be created with a null termination.
//
// This makes string views efficient when passing as parameters. This function here takes a normal std::string
auto take_string(const std::string& s) {
    return s;
}
// so if we call it with a string literal, the compiler must construct a new null terminated string to pass in:
void call_literal() {
    take_string("im a string literal as Im declared directly");
    // NOTE: String literals are marked as const objects as the compiler does not allow augmenting them (they are read only objects). 
    // Therefore, you can only pass string literals to argos accepting const std::string&, std::string, or string_view.
}
// However, if we passed the literal to a function taking a view:
auto take_view(std::string_view s) {
    return s;
}
// The operation is a lot more performant, as the compiler does not need to make a null terminated string out of the literal:
void call_literal_view() {
    take_view("im a string literal as Im declared directly");
    // Compiler creates string_view wrapping "literal"
    // No std::string temporary needed
    // No null-termination check needed (view doesn't require it)
}

// string views can also be constructed from lvalue strings, making them performant for
// passing in lvalue strings too (no copy/move to new null terminated string needed)
void call_lvalue_view() {
    std::string s = "im an lvalue string";
    take_view(s);

    // we can make pointers to string literals as follows:
    auto sPtr = "im a string literal";
    take_view(sPtr); // passing in the const char* pointer is still efficient (only if the types in arguments mismatch i.e if we must convert const char* to std::string)
}
