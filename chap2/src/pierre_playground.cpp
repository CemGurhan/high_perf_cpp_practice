#include "iostream"

int&& testit() {
    return 45;
}

// a and b can only be inferred in the return type
// after the function parameters are parsed, so we have to use arrow return.
template <typename T, typename U>
auto greater(T a, U b) -> decltype(a > b ? a : b)
{
    return a > b ? a : b;
}


void printTemplateFun() {
    std::cout << greater(3, 5) << std::endl;
    std::cout << greater(3.5, 2) << std::endl;
    std::cout << greater(3, 2.5) << std::endl;
}

// struct packing - the way the compiler arranges data in memory for a struct.
// e.g. here we have a struct with 3 ints and 2 doubles. The compiler will 
// arrange the data in memory in a way that optimizes for performance, 
// which may involve adding padding between members to ensure proper alignment. 
struct s {
    int i;
    int i2;
    double d;
    int i3;
    std::string thing;
    double t;
};
