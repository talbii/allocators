#ifndef talbi__STATIC_ALLOCATOR_HPP
#define talbi__STATIC_ALLOCATOR_HPP 

#include <memory>
#include <new>
#include <cstddef>
#include <string>
#include <sstream>
#include <typeinfo>

/*
 * Associated with static_allocator. 
 *  Thrown when attempting to allocate more then MAX_ALLOC bytes. */
struct memory_full : std::bad_alloc {
    std::string m_what;
    memory_full(const std::string& T_str, const std::size_t& max_alloc) {
        std::ostringstream stream;

        stream << "memory_full(" << T_str << ", " << max_alloc << ".\n";
        m_what = stream.str();
    }

    virtual const char* what() const noexcept {
        return m_what.c_str();
    } 
}; };

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
             * (inside (memory_full constructor) may be quite expensive
             * this exception is probably to only be thrown once thus making
             * this call quite negligible. */
            throw memory_full(typeid(T).name(), MAX_ALLOC);
        }
        return &memory[i += n*sizeof(T)];
    }

    constexpr void deallocate(T* p, std::size_t n) { void(); }
};

#endif //talbi__STATIC_ALLOCATOR_HPP
