#include "utils/auto_helpers.hpp"

namespace auto_work::utils {
    int& val_ref() {
        static int v = 42; // static to ensure it lives beyond the function scope
        return v;  
    }

    int& decltype_val_ref() {
        static int v = 42; // static to ensure it lives beyond the function scope
        return v;  
    }
}
