#include <algorithm>
#include <string>

// The compiler will move an object instead of copying if it is an rvalue.

class Class {
    public:
        Class() {}
        // copied in as the param is a const lvalue reference, we can't move into this one
        // as the original data is const, so we must copy. (same would happen if it were a non-const lvalue reference, 
        // as we can't move from an lvalue ref either, because lvalue references are expected to live on).
        auto set_title(const std::string& s) {
            title_ = s;
        }

        auto set_title(std::string&& s) {
            // we must do this as, even if we moved into
            // set_title, or passed an rvalue directly, the rvalue is
            // getting moved into s. Hence, s becomes an lvalue and its data is copied into
            // title_ instead of being moved. The rvalue becomes an lvalue in this func's scope.
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

void some_work_with_passes() {
    auto c = Class{};


}
