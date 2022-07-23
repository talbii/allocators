#ifndef talbi__BENCH_HPP
#define talbi__BENCH_HPP

#include <cstddef>
#include <chrono>
#include <span>
#include <iostream>
#include <vector>
#include "utilities.hpp"

/*
 *  Benchmarks alloc by allocating a vector to size n, 
 *   repeating the allocation count times.
 *
 *   T - the elements of the vector to be allocated
 *   Alloc - the allocator class
 * */

template<class T, class Alloc>
auto bench(std::size_t n, std::size_t count) {
    std::vector<double> stats(count);
    
    for(auto& x : stats) {
        auto start = std::chrono::high_resolution_clock::now();

        std::vector<T> vec(Alloc{});
        for(auto _ = 0; _ < n; _++) vec.push_back(T{});

        auto end = std::chrono::high_resolution_clock::now();
        x = std::chrono::duration<double, std::milli>(end - start).count();
    }

    return stats;
}

/*
 * Prints statistics about the benchmark (average, total, min, max)
 * */

template<class T>
auto bench_print(std::span<const T> data, 
  const std::string& name, std::ostream& stream = std::cout,
  const std::string& units = "ms") {
    auto [min, max] = std::minmax_element(data.begin(), data.end());
    constexpr static auto spaces = "    ";

    auto sum = accum_par(data.begin(), data.end(), 0.0);
    stream << name << ":\n"
           << spaces << "Average: " << sum / data.size() << units 
            << " (N = " << data.size() << ")" << '\n'
           << spaces << "  Total: " << sum << units << '\n'
           << spaces << "    Min: " << *min << units << '\n'
           << spaces << "    Max: " << *max << units << '\n';
}

#endif //talbi__BENCH_HPP
