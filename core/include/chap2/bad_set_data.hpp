#include <vector>

class Widget {
    std::vector<int> data_{};

    public:
    // This is suboptimal as if we pass an lvalue in, the
    // temporary variable x is allocated to, moved into data_ and then
    // deleted.
    void set_data(std::vector<int> x) {
        data_ = std::move(x); // move assignment, as x is an rvalue (function params are rvalues)
    }

    // This is more optimal, as we can avoid a creation of a temporary variable and move, and just copy directly into data_.
    void set_data(const std::vector<int>& x) {
        data_ = x; // copy assignment, as x is an lvalue (named variables are lvalues)
    }

    // we can then still move rvalue refs.
    void set_data(std::vector<int>&& x) noexcept {
        data_ = std::move(x); // move assignment, as x is an rvalue reference (std::move creates an rvalue ref)
    }
};
