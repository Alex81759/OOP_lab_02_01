#ifndef MATRIXITERATOR_H
#define MATRIXITERATOR_H

#include "matrixExceptions.h"

template<typename T>
class Matrix;

template<typename T>
class Iterator {
    private:
        Iterator(Matrix<T>& containerObj, unsigned int index);
        Matrix<T>* matrix;
        unsigned int index;
        void validateAccess() const;
        template<typename U>
        friend class Matrix;
    public:
        explicit Iterator(Matrix<T>& containerObj);
        Iterator(const Iterator<T>& other);
        Iterator<T> next();
        T value();
        bool is_end();
        Iterator<T>& operator++();
        T& operator*();
        bool operator==(const Iterator<T>& other);
        bool operator!=(const Iterator<T>& other);
};

template<typename T>
Iterator<T>::Iterator(Matrix<T>& containerObj) : matrix(&containerObj), index(0) { // matrix
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T>& other) : matrix(other.matrix), index(other.index) {
}

template<typename T>
Iterator<T>::Iterator(Matrix<T>& containerObj, unsigned int index) : matrix(&containerObj), index(index) {
}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (is_end()) {
        throw MatrixIteratorException("Iterator error: cannot move after end iterator.");
    }
    Iterator<T> nextIterator(*matrix, index + 1); // передвигать итератор
    return nextIterator;
}

template<typename T>
T Iterator<T>::value() {
    validateAccess();
    return matrix->getByLinearIndex(index);
}

template<typename T>
bool Iterator<T>::is_end() {
    return matrix == nullptr || index >= matrix->getStorageSize();
}

template<typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (is_end()) {
        throw MatrixIteratorException("Iterator error: cannot increment end iterator.");
    }
    ++index;
    return *this;
}

template<typename T>
T& Iterator<T>::operator*() {
    validateAccess();
    return matrix->getByLinearIndex(index);
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) {
    return matrix == other.matrix && index == other.index;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
    return !(*this == other);
}

template<typename T>
void Iterator<T>::validateAccess() const {
    if (matrix == nullptr || index >= matrix->getStorageSize()) {
        throw MatrixIteratorException("Iterator error: cannot access end iterator.");
    }
}

#endif // MATRIXITERATOR_H
