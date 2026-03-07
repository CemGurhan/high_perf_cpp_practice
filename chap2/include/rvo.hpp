class X {};

auto func() {
    auto x = X{};
    // Tempting to move, but if you don't
    // move on return, the compiler can perform RVO to
    // determine the most optimal way to return the object.
    return x; 
}
