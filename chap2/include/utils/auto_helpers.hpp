#pragma once

namespace auto_work::utils {
    // These can stay as declarations because the return type is EXPLICIT (int&)
    int& val_ref();
    int& decltype_val_ref();

    // These MUST be defined here because the return type is DEDUCED (auto)
    // inline means the compiler calls the function directly in the code, as opposed
    // to the CPU having to jump to the function's memory address.
    inline auto val_ref_wrapper() {
        return val_ref(); 
    }

    inline decltype(auto) decltype_val_ref_wrapper() {
        return decltype_val_ref();
    }
}
