#include "fundamental_compound_type_class.hpp"

void func() {
    auto a = Menu{"Pizza", "Pasta", "Salad"};
    a.select(2);
    // this will cause the underlying items list to be moved and the index copied,
    // hence, the index will remain as 2 on a, but a's underlying items is now empty, so crash on select_item on a.
    auto b = std::move(a); 
    // auto selected = a.select_item(); // CRASH
}
