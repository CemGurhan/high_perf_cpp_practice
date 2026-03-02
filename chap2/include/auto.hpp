#include <iostream>

using std::cout;
using std::endl;

// auto_ref_strip demonstrates how auto can strip 
// references when deducing types.
void auto_ref_strip() {
    int v = 4;
    int& vRef = v;
    auto vCopy = vRef; // auto will strip the reference
    
    vRef = 15; // this will change v
    cout << v << " "; // prints 15

    vCopy = 16; // this won't change v, as reference was stripped
    cout << v << " "; // still prints 15, as vCopy is a copy of the value, not a reference
}

int& val_ref() {
    static int v = 42; // static to ensure it lives beyond the function scope
    return v;  
}

int& decltype_val_ref() {
    static int v = 42; // static to ensure it lives beyond the function scope
    return v;  
}

// decltype_val_wrapper will return an int&,
// because decltype(auto) preserves the reference.
decltype(auto) decltype_val_ref_wrapper() {
    return decltype_val_ref();
}

// val_ref_wrapper will return an int,
// not an int&, because auto will strip the reference.
auto val_ref_wrapper() {
    return val_ref();
}

// decltype_auto demonstrates the difference between auto and decltype(auto) when deducing types, especially in the context of references.
void decltype_auto() {
    decltype(auto) v = val_ref_wrapper();
    decltype(auto) vRefDcl = decltype_val_ref_wrapper();

    cout << "before update:" << "\n";
    cout << v << "\n";
    cout << vRefDcl << "\n"; // use \n instead of endl in performance-critical code to avoid flushing the output buffer

    v = 600;
    vRefDcl = 600;

    decltype(auto) vUpdate = val_ref_wrapper();
    decltype(auto) vRefDclUpdate = decltype_val_ref_wrapper();

    cout << "after update:" << "\n";
    cout << vUpdate << "\n"; // prints 42, as val_ref_wrapper returns auto, so cannot deduce the reference and returns a copy of the value 'v'
    cout << vRefDclUpdate << "\n"; // prints 600, as 'vRefDclUpdate' returns decltype(auto), which preserves the reference, so it reflects the change made to 'vRefDcl'
}
