#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using std::cout;

// for this class, use default constructors as it's simple data (I just did this here as an example)
class Person {
    public:
        Person(std::string n) : name_{std::move(n)} {}

        Person(const Person& other) : name_{other.name_} {} // string already has a copy constructor that does deep copies - simple copy constructor
        Person& operator=(const Person& other) { // cannot use initializer list for assignment operator - name_ hasn't been made yet
            name_ = other.name_;
            return *this; // deref pointer
        }

        // the noexcept here will signal that underlying vector buffers must be moved, not constructed.
        Person(Person&& other) noexcept : name_{std::move(other.name_)}  {} // we must move other as it is an lvalue.

        Person& operator=(Person&& other) noexcept { 
            name_ = std::move(other.name_);
            return *this;
        }
    
    private:
        std::string name_;
};

void move_vector() {
    [[maybe_unused]] Person* pPtr = new Person{"pointer"}; // this results in a pointer made as new creates person on heap

    Person p = Person{"JoeyJoJoShabadoo"};
    std::vector<Person> v = {p, Person{"Gorgonzola"}};
    v.push_back(Person{"Jek"}); // now if the vector resized the Person objects would be moved due to the noexcept on the move constructor

    v.emplace_back(Person{"howdy"}); // this allows us to create an object in place at the back of the vector

    delete pPtr;
}

void erase_if() {
    std::vector<int> v = {1,2,-1,0,9,-10};

    std::erase(v, 0);

    for (auto v : v) {
        cout << v << " "; // 1 2 -1 9 -10
    }

    std::erase_if(v, [](auto x) { return x < 0; });

    cout << "\n";
    for (auto v : v) {
        cout << v << " "; // 1 2 9
    }

    v.erase(std::remove(v.begin(), v.end(), 9));

    cout << "\n";
    for (auto v : v) {
        cout << v << " "; // 1 2
    }
}
