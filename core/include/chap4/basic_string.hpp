#include <string>
#include <iostream>

using std::cout;

// std::string is a typedef for std::basic_string<char>.
// C++ 17 onwards, std::basic_string was guaranteed to be laid
// out contiguously in memory. This means you can pass it into
// an API and have it be treated as a stream of characters (and 
// thus, also std::string).
void basic_string() {
    auto content = std::string(5,'a');

    for (auto c : content)
        cout << c << " oh "; // a oh a oh a ...
}

// basic_string utilizes small object optimization, which
// means it will not be dynamically allocated if a specific size.
