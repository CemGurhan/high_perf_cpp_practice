#include <algorithm>  // std::fill, beign and end

// When stack memory is allocated, it might get allocated to physical memory (a page) 
// once it's accessed in the future. This is so that we can lazily allocate data and don't
// have to worry about storing data up front. This is known as page faulting.
// 
// This can be bad however when we're trying to write low latency code, as page faults can lead
// to memory allocation on a hot path. To avoid this, we can prefault our data.
void prefault_data() {
    // this is a guess - we don't know stack size.
    constexpr auto stack_size = 500u * 1024u;
    // make the array volatile so that the compiler
    // doesn't optimize away the filling of the array 
    // (we need that done right away to prefault).
    // use unsigned char to ensure we touch every single byte in the 
    // array (as a char is a byte). char can hold any value between 0-255,
    // so this can be integers or chars themselves (e.g 'A' -> 65).
    volatile unsigned char mem[stack_size];
    // fill array with zeros. This accesses every byte, triggering
    // a page fault on each new page, forcing prefault.
    std::fill(std::begin(mem), std::end(mem), 0);
}


