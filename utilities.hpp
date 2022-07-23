#ifndef talbi__UTILITIES_HPP
#define talbi__UTILITIES_HPP

#include <numeric>
#include <execution>

template<class Iter, class T>
T accum_par(Iter begin, Iter end, T init = T{}) {
    return std::reduce(std::execution::par, begin, end, init);
}

#endif //talbi__UTILITIES_HPP
