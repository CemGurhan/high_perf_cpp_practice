#include <algorithm>
#include <string>

// The compiler will move an object instead of copying if it is an rvalue.

class Class {
    public:
        Class() {}
        // copied in as the param is a const lvalue reference, we can't move into this one
        // as the original data is const, so we must copy.
        auto set_title(const std::string& s) {
            title_ = s;
        }

        auto set_title(std::string&& s) {
            title_ = std::move(s);
        }

        auto set_title(std::string_view sv) {
            // This performs a direct copy into our internal string.
            // Instead of a raw char being allocated to a std::String then moved in, 
            // the string_view allows a direct copy from the binary data sv points to.
            title_ = sv; 
        }
    
    private:
        std::string title_;
};

auto get_ok() {
    return std::string("OK");
}

// A string_view is just a pointer and a length. It points directly to the "OK" 
// sitting in the binary's read-only data segment. It is massively faster than 
// std::string because it does 0 heap work. It does not own the string data,
// just views.
std::string_view get_view() {
    return "OK"; // Zero allocation. Zero copying.
}

std::string_view get_view_bad() {
    std::string secret = "Temporary Data";
    return std::string_view(secret); // DANGER!
} 
// 'secret' dies here. The view now points to deleted memory.
