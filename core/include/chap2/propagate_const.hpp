#include <experimental/propagate_const>

class Mutable_const {
    public:
    // In a class constructor:
    // - `:` marks the start of the initializer list, which is used to initialize member variables before the constructor body executes.
    // - `ptr_(i)` initializes the member variable `ptr_` with the value of `i` before the constructor starts.
    // - `{}` marks the beginning of the constructor body, where additional initialization or setup can be performed if needed.
    // Assigning data to the class object in the class constructor itself can be slower. E.g. in this example, 
    // if we did:
    //  Mutable_const(int* i) { 
    //      ptr_ = i; 
    //  }
    // then the compiler will create a ptr_ with nullptr and then assign i to it. If this is a large class with many members, 
    // this can lead to unnecessary overhead. By using the initializer list, we can directly initialize ptr_ with i, which is more efficient.
    // ptr invoked before prt2 as appears first in class list
        Mutable_const(int* i) : ptr2_{i}, ptr_{i + 1} { ptr_ = i;}
        void set_ptr(int i) const {
            // this compiles, despite fucntion being declared const.
            // This is because the ptr_ itself is not modified, but the data it points to
            // is modifiable.
            *ptr_ = i;
            // val_ = i; // won't compile as every member of a class inside a const function is made const.
        }
    private:
        int* ptr_;
        int* ptr2_;
        int val_ {};
};


class Propagate_const {
    public:
        Propagate_const(int* i) : ptr_{i} {}
        void set_ptr(int i) const {
            // these do not compile as we are trying to
            // modify data through a const pointer.
            // ptr_ = i;
            // *ptr_ = i;
            // val_ = i; // won't compile as every member of a class inside a const function is made const.
        }

    private:
        std::experimental::propagate_const<int*> ptr_ = nullptr;
        int val_ {};
};
