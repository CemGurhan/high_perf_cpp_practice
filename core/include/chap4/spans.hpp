#include <array>
#include <span>


// When arrays are passed into functions, they lose their size information.
// This is known as array decay
// void array_decay(float buffer[]) {
//     const auto n = std::size(buffer); // won't compile
// }


// instead, we cna use spans. Spans contain pointers to the array/vector memory, as
// well as the size information, so they can be passed without decay.
void use_span(std::span<float> buffer) {
    const auto n = std::size(buffer); // compiles
}

void pass_to_span() {
    float buffer[256];

    use_span(buffer); // fine

    auto v = std::vector<float>{1.0, 2.5, 3.7};

    use_span(v); // also fine
}
