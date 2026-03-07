#include <algorithm>

class Buffer {
    public:
        // Copy constructor (operator not needed here because we're creating brand new objects - no potential for shallow copy).
        Buffer(const Buffer& other) : size_{other.size_} {
            // No 'if (this != &other)' needed! You can't be born from yourself.
            // No 'delete[] ptr_' needed! You don't have any old memory to clean up yet.
            ptr_ = new float[size_]; // buffer of floats
            // first param start, second param end, third param destination
            std::copy(other.ptr_, other.ptr_ + size_, ptr_);
        }

        // Copy assignment
        // We need 'operator=' because the default '=' would only copy the pointer address (Shallow Copy).
        // If we did that, two buffers would point to the same memory, leading to a crash (Double Free).
        Buffer& operator=(const Buffer& other) {
            // Check for 'self-assignment' (e.g., b1 = b1). 
            // We check addresses to ensure we don't delete our own data before trying to copy it.
            if (this != &other) { 
                // We must manually release our current memory to avoid a "Memory Leak."
                delete[] ptr_; // we must call delete[] because we used new[] to allocate the memory.

                // Update our size to match the source buffer.
                size_ = other.size_;

                // Request a brand new block of memory from the system.
                ptr_ = new float[size_];

                // Manually trigger the "Deep Copy."
                // We reach into the other buffer's memory and duplicate every single float.
                std::copy(other.ptr_, other.ptr_ + size_, ptr_);
            }

            // We return a reference to ourselves (*this).
            // This is required so we can "chain" assignments, like: a = b = c;
            return *this;
        }

        // Destructor
        ~Buffer() {
            delete [] ptr_;
            ptr_ = nullptr; // Not strictly necessary, but it can help prevent "Dangling Pointer" bugs.
        }

        // Move constructor, moves take rvalue references as rvalue references are temporary objects 
        // that are about to be destroyed, so we can "steal" their resources without worrying about leaving 
        // them in an invalid state. 
        Buffer(Buffer&& other) noexcept : size_{other.size_}, ptr_{other.ptr_} {
            other.ptr_ = nullptr;
            other.size_ = 0;
        }

        // Move assignment
        Buffer& operator=(Buffer&& other) noexcept  {
            if (this != &other) {     // 1. Self-assignment check
                delete[] ptr_;        // 2. Clean up our old junk
                ptr_ = other.ptr_;    // 3. Steal their junk
                size_ = other.size_;
                other.ptr_ = nullptr; // 4. Leave them with nothing
                other.size_ = 0;
            }
            return *this;
        }
    private:
        int size_;
        float* ptr_;
};

// uninitialized_copy
