void compile_time_const() {
    // constexpr tells the compiler that this must be evaluated at
    // compile time. 
    constexpr int nCompileTime = 100;

    // standard const doesn't make this contract and this value will
    // be evaluated at runtime.
    const int nRuntime = 100;
}

// constexpr is useful as older compilers cannot always distinguish that
// const int ... is a compile time constant. With constexpr we can confirm
// to all compilers that the variable is compile time constant:

// Compiler A: "OK, I recognize this is compile-time"
// Compiler B: "Error: size might be runtime"
// Compiler C: "Warning: might not be compile-time"

// Use constexpr for values needed at compile-time (array sizes, templates)
// Use const for runtime values that don't change
// Use constexpr when in doubt—it's more explicit and portable


