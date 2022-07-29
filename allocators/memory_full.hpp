#ifndef talbi__MEMORY_FULL_HPP
#define talbi__MEMORY_FULL_HPP

#include <string>
#include <cstddef>
#include <new>
#include <sstream>

/*
 * Associated with static_allocator and global_static_allocator.
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
};

#endif //talbi__MEMORY_FULL_HPP
