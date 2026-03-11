#include <deque>

void use_deque() {
    auto d = std::deque<int>{1,2,3,4};

    d.push_front(5); // 5,1,2,3,4
}
