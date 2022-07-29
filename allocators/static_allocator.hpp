#ifndef talbi__STATIC_ALLOCATOR_HPP
#define talbi__STATIC_ALLOCATOR_HPP 

#include <memory>
#include <typeinfo>
#include "memory_full.hpp"

/*
 * static_allocator<T, MAX_ALLOC> is an allocator which will only allocate
 * MAX_ALLOC bytes. Any attempt to allocate more shall cause an exception (memory_full)
 * to be thrown.*/
template<class T, std::size_t MAX_ALLOC>
struct static_allocator : std::allocator<T> {
    char *memory;
    std::size_t i;
    
    constexpr static_allocator() : memory(new char[MAX_ALLOC]), i(0) {}
    virtual ~static_allocator() { delete [] memory; }

    [[nodiscard]] constexpr T* allocate(std::size_t n) {
        if(i + n >= MAX_ALLOC) {
            /*note: While constructing a type_info and ostringstream 
             * (inside memory_full constructor) may be quite expensive
             * this exception is probably to only be thrown once thus making
             * this call quite negligible. */
            throw memory_full(typeid(T).name(), MAX_ALLOC);
        }
        return &memory[i += n*sizeof(T)];
    }

    constexpr void deallocate(T* p, std::size_t n) { void(); }
};

#endif //talbi__STATIC_ALLOCATOR_HPP
