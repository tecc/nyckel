#ifndef NYCKEL_GUARD_HPP
#define NYCKEL_GUARD_HPP

#include <mutex>
namespace nyckel {
    template<typename T>
    class Guard {
    public:
        Guard();
        Guard(T t);

        T& get();
        T& operator =(T val);


    private:
        T value;
        std::mutex mutex;
    };
};

#include <nyckel/Guard.tcc>

#endif
