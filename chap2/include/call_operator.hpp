#include <iostream>

using std::cout;

class Multiplier {
    public:
        Multiplier(int factor) : factor_(factor) {}

        int operator()(int value) const { // this operator allows us to call Multiplier as if it were a function
            return value * factor_;
        }
    private:    
        int factor_;
};

void operator_example()
 {
    auto m = Multiplier{5}; // factor 5
    auto res = m(10);

    std::cout << res << "\n"; // print 50
 } 
