#include <string>
#include <initializer_list>
#include <vector>

class Menu {
    public:
    // initializer list allows you to create the vector with the class, not having to 
    // create a vector then pass it into the class constructor.
        Menu(const std::initializer_list<std::string>& items) : items_{items} {}
        auto select(int i) {
            index_ = i;
        }

        auto select_item() const {
            return index_ != -1 ? items_[index_] : "";
        }

    private:
        std::vector<std::string> items_;
        int index_ {-1};
};

// MenuSafe is the better way to move when fundamental and compound types are semantically mixed.
class MenuSafe {
    public:
        MenuSafe(const std::initializer_list<std::string>& items) : items_{items} {}
        // this is safer as now, items_ is moved away from 
        // the original MenuSafe, as well as the index_. Now, index_ will be
        // -1 and we won't select out of bounds.
        MenuSafe(MenuSafe&& other) noexcept {
            std::swap(items_, other.items_); 
            std::swap(index_, other.index_);
        }

        MenuSafe& operator=(MenuSafe&& other) noexcept {
            if (this != &other) {
                std::swap(items_, other.items_); 
                std::swap(index_, other.index_);
            }
            return *this;
        }

        auto select(int i) {
            index_ = i;
        }

        auto select_item() const {
            return index_ != -1 ? items_[index_] : "";
        }

    private:
        std::vector<std::string> items_;
        int index_ {-1};
};
