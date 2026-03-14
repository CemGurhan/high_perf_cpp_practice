#include <vector>
#include <queue>
#include <iostream>

using std::cout;

struct Hit {
    float rank_{};
};


void priority_queue_least_func() {
    // cmp signature for a priority_queue must take 2 const references and return a bool
    auto cmp = [](const Hit& a, const Hit& b) {
        // if flipped, greatest elements would go on top.
        // b's relationship wrt to a is what dictates element ordering.
        return a.rank_ > b.rank_; 
    };

    // second argument in template list must be a random access container.
    auto pq = std::priority_queue<Hit, std::vector<Hit>, decltype(cmp)>{cmp};

    auto h1 = Hit{1};
    auto h2 = Hit{5};
    auto h3 = Hit{-10};

    pq.push(h1);
    pq.push(h2);
    pq.push(h3);

    cout << "with least at top" << "\n";

    cout << pq.top().rank_ << "\n"; // -10

    pq.pop(); // pop element off top (does not return)

    cout << pq.top().rank_ << "\n"; // 1
}

void priority_queue_most_func() {
    // cmp signature for a priority_queue must take 2 const references and return a bool
    auto cmp = [](const Hit& a, const Hit& b) {
        // if flipped, greatest elements would go on top.
        // b's relationship wrt to a is what dictates element ordering.
        return a.rank_ < b.rank_; 
    };

    // second argument in template list must be a random access container.
    auto pq = std::priority_queue<Hit, std::vector<Hit>, decltype(cmp)>{cmp};

    auto h1 = Hit{1};
    auto h2 = Hit{5};
    auto h3 = Hit{-10};

    pq.push(h1);
    pq.push(h2);
    pq.push(h3);

    cout << "with most at top" << "\n";

    cout << pq.top().rank_ << "\n"; // 5

    pq.pop(); // pop element off top (does not return)

    cout << pq.top().rank_ << "\n"; // 1
}
