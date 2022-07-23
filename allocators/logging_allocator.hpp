#ifndef talbi__LOGGING_ALLOCATOR_HPP
#define talbi__LOGGING_ALLOCATOR_HPP

#include <memory>
#include <iostream>

template<class T>
struct logging_allocator : std::allocator<T> {
    using super = std::allocator<T>;

    [[nodiscard]] constexpr T* allocate(std::size_t n) {
        auto *p = super::allocate(n);
        std::clog << "Allocated " << n << " bytes at "
                  << reinterpret_cast<void*>(p) << '\n';
        return p;
    }

    constexpr void deallocate(T *p, std::size_t n) noexcept {
        std::clog << "Deallocating " << n << " bytes at "
                  << reinterpret_cast<void*>(p) << '\n';
        super::deallocate(p, n);
    }
};

#endif //talbi__LOGGING_ALLOCATOR_HPP
