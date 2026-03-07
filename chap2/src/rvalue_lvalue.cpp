#include "rvalue_lvalue.hpp"

// rvalues are created by std::move and function returns.
// They are temporary objects that are about to be destroyed, 
// so we can "steal" their resources without worrying about leaving them in an invalid state.
// This is why they are moved instead of copied.

void class_set_tittles() {
    auto c = Class{};

    auto str = std::string("OK");
    c.set_title(str); // copy assigned due to str being lvalue
    c.set_title(std::move(str)); // move assigned due to std::move(str) being an rvalue (std::move creates an rvalue ref)
    c.set_title(get_ok()); // move assigned due to get_ok() being an rvalue (function returns are rvalues)

    auto strRet = get_ok();
    c.set_title(strRet); // copy assigned due to strRet being an lvalue (named variables are lvalues)

    const auto strConst = get_ok();
    // copy assigned as std::move(strConst) is an rvalue reference to a const object, and we cannot move from const objects, 
    // so it falls back to copy assignment.
    c.set_title(std::move(strConst)); 

    // goes to a move assignment as get_view() returns a string_view, which is an rvalue, 
    // and string_view can be directly assigned to a std::string without needing to copy 
    // the data, so it performs a move assignment.
    c.set_title(get_view());
}
