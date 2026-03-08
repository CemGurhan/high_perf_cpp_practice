#include <string>



// lvalue ref: modifiable unless const, sow e msut be careful.
auto copy_and_swap(std::string& str) {
    auto tmp = std::string{str};
    // if the additions to tmp came from a function and could throw an exception, 
    // we don't want to leave str in a partially updated state, so create a copy
    // and swap at end.
    tmp += "hi"; 
    tmp += "bye";
    std::swap(tmp, str);
    return str;
}

// This is safe as the string is copied in, 
// so any exception won't leave it in a bad state.
auto copy_and_swap(std::string str) {
    str += "hi"; 
    str += "bye";
    return str;
}

// This is safe as the reference is an rvalue one,
// so the param data is not expected to live on past the function
// scope anyway.
auto copy_and_swap(std::string&& str) {
    str += "hi"; 
    str += "bye";
    return str;
}
