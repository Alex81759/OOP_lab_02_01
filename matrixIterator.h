#ifndef MATRIXITERATOR_H
#define MATRIXITERATOR_H

#include "matrixExceptions.h"

template<typename T>
class Matrix;

template<typename T>
class Iterator {
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

private:
    Iterator(Matrix<T>& containerObj, unsigned int index);

    Matrix<T>* matrix_;
    unsigned int index_;

    void validateAccess() const;

    template<typename U>
    friend class Matrix;
};

template<typename T>
Iterator<T>::Iterator(Matrix<T>& containerObj)
    : matrix_(&containerObj), index_(0) {
}

template<typename T>
Iterator<T>::Iterator(const Iterator<T>& other)
    : matrix_(other.matrix_), index_(other.index_) {
}

template<typename T>
Iterator<T>::Iterator(Matrix<T>& containerObj, unsigned int index)
    : matrix_(&containerObj), index_(index) {
}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (is_end()) {
        throw MatrixIteratorException("Iterator error: cannot move after end iterator.");
    }

    Iterator<T> nextIterator(*matrix_, index_ + 1);
    return nextIterator;
}

template<typename T>
T Iterator<T>::value() {
    validateAccess();
    return matrix_->getByLinearIndex(index_);
}

template<typename T>
bool Iterator<T>::is_end() {
    bool result = false;

    if (index_ >= matrix_->getStorageSize()) {
        result = true;
    }

    return result;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++() {
    if (is_end()) {
        throw MatrixIteratorException("Iterator error: cannot increment end iterator.");
    }

    ++index_;
    return *this;
}

template<typename T>
T& Iterator<T>::operator*() {
    validateAccess();
    return matrix_->getByLinearIndex(index_);
}

template<typename T>
bool Iterator<T>::operator==(const Iterator<T>& other) {
    bool result = false;

    if (matrix_ == other.matrix_ && index_ == other.index_) {
        result = true;
    }

    return result;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
    bool result = true;

    if (*this == other) {
        result = false;
    }

    return result;
}

template<typename T>
void Iterator<T>::validateAccess() const {
    if (index_ >= matrix_->getStorageSize()) {
        throw MatrixIteratorException("Iterator error: cannot access end iterator.");
    }
}

#endif // MATRIXITERATOR_H
