#include <string>
#include <algorithm>
#include <vector>

// for this class, use default constructors as it's simple data (I just did this here as an example)
class Person {
    public:
        Person(std::string n) : name_{n} {}

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
    delete pPtr;
}
