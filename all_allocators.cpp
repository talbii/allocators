#include <iostream>
#include <vector>
#include "bench.hpp"

// Allocators
#include <memory>
#include "aggressive_allocator.hpp"
#include "static_allocator.hpp"

int main(void) {
    constexpr std::size_t n = 100'000; 
    constexpr std::size_t count = 10'000; 

    using T = int;

    bench_print( std::span<const double>{bench<T, std::allocator<T>> (n, count)}, "std::allocator<int>" );
    bench_print( std::span<const double>{bench<T, aggressive_allocator<T, 4*16384>> (n, count)},
            "aggressive_allocator<int, 65,536>" );
    bench_print( std::span<const double>{bench<T, static_allocator<T, 1LL<<25>> (n, count)}, 
            "static_allocator<int, 32MB>");
        
}
