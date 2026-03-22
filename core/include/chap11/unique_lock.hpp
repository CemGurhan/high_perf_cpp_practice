#include <thread>

struct Account {
    Account() {}
    int balance_{0};
    std::mutex mu_{};
 };

void unique_lock(Account& from, Account& to, int amount) {
    // create unique locks for both mutexes that will be locked later all at once
    auto lock1 = std::unique_lock<std::mutex>{from.mu_, std::defer_lock};
    auto lock2 = std::unique_lock<std::mutex>{to.mu_, std::defer_lock};

    std::lock(lock1, lock2); // lock both mutexes at the same time

    // safely transfer amount without deadlock
    from.balance_ -= amount;
    to.balance_ += amount;
}

void scoped_lock(Account& from, Account& to, int amount) {
    std::scoped_lock lock{from.mu_, to.mu_}; // lock both at same time.

    // safely transfer amount with no deadlock.
    from.balance_ -= amount;
    to.balance_ += amount;
 }
