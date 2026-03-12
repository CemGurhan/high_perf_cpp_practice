#include <map>
#include<string>
#include <boost/functional/hash.hpp>

void map_set_ordered() {
    auto mO = std::map<int, int>{}; // ordered map

    mO[3] = 9; // goes onto an underlying binary tree O(log(N)) operation.
}

class person {
    public: 
        person(int age, std::string name) : age_{age}, name_{name} {}
        auto age() const { return age_; }
        auto name() const { return name_; }
    private:
        int age_;
        std::string name_;
};

void map_unordered() {
    auto person_eq = [](const person& lhs, const person& rhs) {
        return lhs.name() == rhs.name() && lhs.age() == rhs.age();
    };

    auto person_hash = [](const person& person) {
        auto seed = size_t{0}; // use size_t over uint as size_t matches architecture of system (e.g. is 64 bits on 64bit)
        boost::hash_combine(seed, person.name()); 
        boost::hash_combine(seed, person.age()); 
        return seed;
    };
}
