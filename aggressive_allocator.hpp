#ifndef talbi__AGGRESSIVE_ALLOCATOR_HPP
#define talbi__AGGRESSIVE_ALLOCATOR_HPP

#include <vector>
#include <memory>
#include <utility>


/*
 * aggressive_allocator is an allocator which attempts to reduce allocation calls by allocating memory in big chunks.
 *  On initialization aggressive_allocator will allocate `aggression` elements of type T.
 *  On each subsequent allocation aggressive_allocator will attempt to return from memory already allocated. 
 *   If out of memory, it shall allocate another `aggression` elements.
 *   If allocation request is larger then aggression, allocate using std::allocator<T>.
 *
 * ! Note: memory allocatedu sing std::allocator<T> is probably not freed.
 * */
template<class T, std::size_t aggression>
struct aggressive_allocator : std::allocator<T> { // potential memory leak
    private:
       using pack = std::pair<T*, std::size_t>;  // aggression should be much bigger than typical allocation request
       using super = std::allocator<T>;

       std::vector<pack> data;
    public:
       aggressive_allocator() : data{{nullptr,0}} {
           data.begin()->first = new T[aggression];
       }
       virtual ~aggressive_allocator() {
           for(auto& d : data) delete[] d.first;
       }

       [[nodiscard]] constexpr T* allocate( std::size_t n ) {
           if(n > aggression) return super::allocate(n);
           auto &mem = data.back();
           if(mem.second + n >= aggression) {
               data.push_back({new T[aggression], aggression});
           }
           auto &current = data.back();
           current.second += n;
           return current.first[current.second - n];
       }
       constexpr void deallocate( T* p, std::size_t n ) {
           void();
       }
};

#endif //talbi__AGGRESSIVE_ALLOCATOR_HPP
