#ifndef talbi__GLOBAL_STATIC_ALLOCATOR_HPP
#define talbi__GLOBAL_STATIC_ALLOCATOR_HPP

#include <memory>
#include "memory_full.hpp"

template<class T>
struct global_static_allocator;

template<>
struct global_static_allocator<void> {
    static constexpr std::size_t MAX_ALLOC = 1LL << 28; // 256 MB
    static std::size_t i;
    static char memory[MAX_ALLOC];  
};

std::size_t global_static_allocator<void>::i = 0;
char global_static_allocator<void>::memory[global_static_allocator::MAX_ALLOC] = {0};

template<class T>
struct global_static_allocator : std::allocator<T> {
    using mem = global_static_allocator<void>;

   [[nodiscard]] constexpr T* allocate(std::size_t n) {
       if(mem::i + n >= mem::MAX_ALLOC) throw memory_full(typeid(T).name(), mem::MAX_ALLOC);
       return (T*) &mem::memory[mem::i += sizeof(T) * n];     
   }

    constexpr void deallocate(T *p, std::size_t n) { void(); }
};

#endif //talbi__GLOBAL_STATIC_ALLOCATOR_HPP
