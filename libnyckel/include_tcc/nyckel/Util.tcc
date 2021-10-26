#ifndef NYCKEL_UTIL_TCC
#define NYCKEL_UTIL_TCC

template<typename T>
uint64_t nyckel::util::hash(std::basic_string<T> str) {
    return std::hash<std::string>()(str);
}

#endif