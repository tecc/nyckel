#ifndef NYCKEL_UTIL_TCC
#define NYCKEL_UTIL_TCC

template<typename T>
uint64_t nyckel::util::hash(std::basic_string<T> str) {
    return std::hash<std::string>()(str);
}

template<typename T>
std::vector<std::basic_string<T>> nyckel::util::split(const std::basic_string<T>& str, const std::basic_string<T>& delimiter) {
    typedef std::basic_string<T> s;
    std::vector<s> vector;
    s current = str;
    typename s::size_type index;
    while ((index = current.find(delimiter)) != s::npos) {
        s part = current.substr(0, index);
        vector.push_back(part);
        current = current.substr(index);
    }
    return vector;
}

#endif