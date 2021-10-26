#ifndef NYCKEL_GUARD_TCC
#define NYCKEL_GUARD_TCC
#include <nyckel/Guard.hpp>

template<typename T>
nyckel::Guard<T>::Guard() : value() {
}
template<typename T>
nyckel::Guard<T>::Guard(T t) : value(t) {
}
template<typename T>
T& nyckel::Guard<T>::get() {
    this->mutex.lock();
    T* copy = &this->value;
    this->mutex.unlock();
    return *copy;
}
template<typename T>
T& nyckel::Guard<T>::operator=(T val) {
    this->mutex.lock();
    T result = this->value = val;
    this->mutex.unlock();
    return result;
}
#endif