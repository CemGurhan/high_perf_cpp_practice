#include <array>

// std::forward allows the compiler to decide whether something
// should be moved or copied.

class WorkerPusher {
    public:
        // std::forward keeps item an rvalue when we push it into do_push. Hence, it moves it
        // into do_push.
        void Push(std::string&& item, int i) { do_push(std::forward<decltype(item)>(item), i); } 
        
    private:
        std::array<std::string, 10> items_; 
        void do_push(auto&& v, int i) {
            if (i >= items_.size() ) {
                return
            }

            // std::forward keeps v an rvalue as we push it into items vector.
            items_[i] = std::forward<decltype(v)>(v);
        }
};


