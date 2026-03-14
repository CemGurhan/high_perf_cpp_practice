#include <map>
#include<string>
#include <boost/functional/hash.hpp>
#include <unordered_set>

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

    // Note: we must have the hash and equality be decltype as lambdas are anonymous types,
    // in order to instantiate templates we need types, decltype extracts the type out of the lambda.
    using Set = std::unordered_set<person, decltype(person_hash), decltype(person_eq)>; 

    auto persons = Set{100, person_hash, person_eq};

    auto personsNonTemplate = std::unordered_set<person, decltype(person_hash), decltype(person_eq)>{100, person_hash, person_eq};
}

struct PersonHash {
    size_t operator()(const person& p) const {
        auto seed = size_t{0};
        boost::hash_combine(seed, p.name()); 
        boost::hash_combine(seed, p.age()); 
        return seed;
    }
};

struct PersonEquality {
    bool operator()(const person& lhs, const person& rhs) const {
        return lhs.name() == rhs.name() && lhs.age() == rhs.age();
    }
};


void map_unordered_struct() {
    // call operator structs can be passed in directly to template as they're objects.
    std::unordered_set<person, PersonHash, PersonEquality> persons;

    auto p = person{30, "Joey"};

    persons.emplace(p);
    
    // key person val int
    std::unordered_map<person, int, PersonHash, PersonEquality> personsMap;

    personsMap[p] = 115;

    personsMap.rehash(50); // re-hashes all elements to 50 buckets

    auto lf = personsMap.max_load_factor();

    personsMap.max_load_factor(0.8); // 0.8 elements per bucket max - higher load factor max -> more collisions (less buckets)

    // reserve is "better" than rehash in a way as it lets you think in elements.
    personsMap.reserve(100); // if max_lf = 0.75 -> reserving 100 space for elements creates 134 buckets (100/0.75)
    personsMap.rehash(100); // creates exactly 100 buckets (might exceed max load factor of 0.75 (e.g w 100 elements load factor becomes 1))

    // use reserve for most cases, use rehash if you want exact bucket control
}
