#ifndef NYCKEL_UTIL_HPP
#define NYCKEL_UTIL_HPP

#include <cstdint>
#include <uuid.h>
#include <vector>

namespace nyckel::util {
    typedef std::basic_string_view<uint8_t> ByteView;

    template<typename T>
    uint64_t hash(std::basic_string<T> str);

    template<typename T>
    std::vector<std::basic_string<T>> split(const std::basic_string<T>& str, const std::basic_string<T>& delimiter);

    uuids::uuid generateUuid();
}

#include <nyckel/Util.tcc>

#endif
