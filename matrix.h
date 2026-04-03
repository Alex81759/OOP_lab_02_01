#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <new>
#include <cmath>
#include "matrixExceptions.h"
#include "matrixIterator.h"

template<typename T>
class Iterator;

template<typename T>
class Matrix {
    private:
        unsigned int rows;
        unsigned int columns;
        T* data;
        static constexpr double doubleEpsilon = 1e-9; //
        void allocateMemory(unsigned int count);
        void copyData(const T* source, unsigned int count);
        void fillDefaultValues(unsigned int count); //
        void releaseMemory(); //
        void validateIndices(unsigned int i, unsigned int j) const; //
        void validateEqualSize(const Matrix<T>& matr) const; //
        void validateMultiplicationSize(const Matrix<T>& matr) const;
        void validateInitializerList(std::initializer_list<std::initializer_list<T>> lst) const;
        unsigned getLinearIndex(unsigned int i, unsigned int j) const;
        unsigned getStorageSize() const;
        T& getByLinearIndex(unsigned int index);
        const T& getByLinearIndex(unsigned int index) const;
        template<typename U>
        friend class Iterator;
    public:
        Matrix(unsigned int n, unsigned int m);
        Matrix(const Matrix<T>& matr);
        Matrix(Matrix<T>&& matr) noexcept;
        explicit Matrix(std::initializer_list<std::initializer_list<T>> lst);
        ~Matrix();
        Matrix<T>& operator=(const Matrix<T>& matr);
        Matrix<T>& operator=(Matrix<T>&& matr) noexcept;
        Matrix<T>& operator+=(const Matrix<T>& matr);
        Matrix<T>& operator-=(const Matrix<T>& matr);
        template<typename _T>
        friend Matrix<_T> operator+(const Matrix<_T>& m1, const Matrix<_T>& m2);
        template<typename _T>
        friend Matrix<_T> operator-(const Matrix<_T>& m1, const Matrix<_T>& m2);
        template<typename _T>
        friend Matrix<_T> operator*(const Matrix<_T>& m1, const Matrix<_T>& m2);
        template<typename _T>
        friend Matrix<_T> operator+(const Matrix<_T>& m1, double num);
        template<typename _T>
        friend Matrix<_T> operator-(const Matrix<_T>& m1, double num);
        template<typename _T>
        friend Matrix<_T> operator/(const Matrix<_T>& m1, double num);
        template<typename _T>
        friend Matrix<_T> operator*(const Matrix<_T>& m1, double num);
        template<typename _T>
        friend std::ostream& operator<<(std::ostream& os, const Matrix<_T>& matr);
        void set_elem(unsigned int i, unsigned int j, const T& elem);//
        T& get_elem(unsigned int i, unsigned int j);
        T& operator()(unsigned int i, unsigned int j);
        bool is_square() const;
        unsigned int get_row() const;
        unsigned int get_columns() const;
        Iterator<T> iterator_begin();
        Iterator<T> iterator_end();
};

template<typename T>
Matrix<T>::Matrix(unsigned int n, unsigned int m) : rows(n), columns(m), data(nullptr) {
    if (n == 0 || m == 0) {
        throw MatrixSizeException("Matrix size error: row and column counts must be greater than zero.");
    }
    allocateMemory(rows * columns);
    fillDefaultValues(rows * columns);
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& matr) : rows(matr.rows), columns(matr.columns), data(nullptr) {
    const unsigned int size = rows * columns;
    if (size > 0) {
        allocateMemory(size);
        copyData(matr.data, size);
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& matr) noexcept : rows(matr.rows), columns(matr.columns), data(matr.data) { //
    matr.rows = 0;
    matr.columns = 0;
    matr.data = nullptr;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> lst) : rows(static_cast<unsigned int>(lst.size())), columns(0), data(nullptr) {//
    if (lst.size() == 0) {
        throw MatrixSizeException("Matrix size error: initializer list cannot be empty.");
    }
    validateInitializerList(lst);
    columns = static_cast<unsigned int>(lst.begin()->size());
    allocateMemory(rows * columns);
    fillDefaultValues(rows * columns);
    unsigned int rowIndex = 0; //
    for (const auto& row : lst) {
        unsigned int columnIndex = 0;
        for (const auto& value : row) {
            data[getLinearIndex(rowIndex, columnIndex)] = value;
            ++columnIndex;
        }
        ++rowIndex;
    }
}

template<typename T>
Matrix<T>::~Matrix() {
    releaseMemory();
}
// присваивание жолжно ыть реализовано через конструктор копирования
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matr) {
    if (this != &matr) {
        T* newData = nullptr;
        const unsigned int newSize = matr.rows * matr.columns;
        if (newSize > 0) {
            newData = new (std::nothrow) T[newSize];
            if (newData == nullptr) {
                throw MatrixMemoryException("Memory error: failed to allocate memory for matrix assignment.");
            }
            for (unsigned int index = 0; index < newSize; ++index) {
                newData[index] = matr.data[index];
            }
        }
        releaseMemory();
        data = newData;
        rows = matr.rows;
        columns = matr.columns;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matr) noexcept { // использовать конструктор копирования в операторе копирования или наоборот?
    if (this != &matr) {
        releaseMemory();
        rows = matr.rows;
        columns = matr.columns;
        data = matr.data;
        matr.rows = 0;
        matr.columns = 0;
        matr.data = nullptr;
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matr) {
    validateEqualSize(matr);
    const unsigned int size = getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        data[index] += matr.data[index];
    }
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matr) {
    validateEqualSize(matr);
    const unsigned int size = getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        data[index] -= matr.data[index];
    }
    return *this;
}

template<typename T>
void Matrix<T>::set_elem(unsigned int i, unsigned int j, const T& elem) {
    validateIndices(i, j);
    data[getLinearIndex(i, j)] = elem;
}

template<typename T>
T& Matrix<T>::get_elem(unsigned int i, unsigned int j) {
    validateIndices(i, j);
    return data[getLinearIndex(i, j)];
}

template<typename T>
T& Matrix<T>::operator()(unsigned int i, unsigned int j) {
    return get_elem(i, j);
}

template<typename T>
bool Matrix<T>::is_square() const {
    return rows == columns;
}

template<typename T>
unsigned int Matrix<T>::get_row() const {
    return rows;
}

template<typename T>
unsigned int Matrix<T>::get_columns() const {
    return columns;
}

template<typename T>
void Matrix<T>::allocateMemory(unsigned int count) {
    if (count == 0) {
        data = nullptr;
    } else {
        data = new (std::nothrow) T[count];
        if (data == nullptr) {
            throw MatrixMemoryException("Memory error: failed to allocate matrix storage.");
        }
    }
}

template<typename T>
void Matrix<T>::copyData(const T* source, unsigned int count) {
    for (unsigned int index = 0; index < count; ++index) {
        data[index] = source[index];
    }
}

template<typename T>
void Matrix<T>::fillDefaultValues(unsigned int count) {
    for (unsigned int index = 0; index < count; ++index) {
        data[index] = T();
    }
}

template<typename T>
void Matrix<T>::releaseMemory() {
    delete[] data;
    data = nullptr;
}

template<typename T>
void Matrix<T>::validateIndices(unsigned int i, unsigned int j) const {
    if (i >= rows || j >= columns) {
        throw MatrixIndexException("Index error: matrix indices are out of range.");
    }
}

template<typename T>
void Matrix<T>::validateEqualSize(const Matrix<T>& matr) const {
    if (rows != matr.rows || columns != matr.columns) {
        throw MatrixSizeException("Size error: matrix dimensions must be equal.");
    }
}

template<typename T>
void Matrix<T>::validateMultiplicationSize(const Matrix<T>& matr) const {
    if (columns != matr.rows) {
        throw MatrixSizeException("Size error: left matrix columns must be equal to right matrix rows.");
    }
}

template<typename T>
void Matrix<T>::validateInitializerList(std::initializer_list<std::initializer_list<T>> lst) const {
    const unsigned int firstRowSize = static_cast<unsigned int>(lst.begin()->size());
    if (firstRowSize == 0) {
        throw MatrixSizeException("Matrix size error: row in initializer list cannot be empty.");
    }
    for (const auto& row : lst) {
        if (row.size() != firstRowSize) {
            throw MatrixSizeException("Initializer list error: all rows must have the same length.");
        }
    }
}

template<typename T>
unsigned int Matrix<T>::getLinearIndex(unsigned int i, unsigned int j) const {
    return i * columns + j;
}

template<typename T>
unsigned int Matrix<T>::getStorageSize() const {
    return rows * columns;
}

template<typename T>
T& Matrix<T>::getByLinearIndex(unsigned int index) {
    if (index >= getStorageSize()) {
        throw MatrixIndexException("Index error: linear index is out of range.");
    }
    return data[index];
}

template<typename T>
const T& Matrix<T>::getByLinearIndex(unsigned int index) const {
    if (index >= getStorageSize()) {
        throw MatrixIndexException("Index error: linear index is out of range.");
    }
    return data[index];
}

template<typename _T>
Matrix<_T> operator+(const Matrix<_T>& m1, const Matrix<_T>& m2) {
    m1.validateEqualSize(m2);
    Matrix<_T> result(m1); // += везде
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = m1.data[index] + m2.data[index];
    }
    return result;
}

template<typename _T>
Matrix<_T> operator-(const Matrix<_T>& m1, const Matrix<_T>& m2) {
    m1.validateEqualSize(m2);
    Matrix<_T> result(m1);
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = m1.data[index] - m2.data[index];
    }
    return result;
}

template<typename _T>
Matrix<_T> operator*(const Matrix<_T>& m1, const Matrix<_T>& m2) {
    m1.validateMultiplicationSize(m2);
    Matrix<_T> result(m1.rows, m2.columns);
    for (unsigned int i = 0; i < m1.rows; ++i) {
        for (unsigned int j = 0; j < m2.columns; ++j) {
            _T sum = _T();
            for (unsigned int k = 0; k < m1.columns; ++k) {
                sum += m1.data[m1.getLinearIndex(i, k)] * m2.data[m2.getLinearIndex(k, j)];
            }
            result.data[result.getLinearIndex(i, j)] = sum;
        }
    }
    return result;
}

template<typename _T>
Matrix<_T> operator+(const Matrix<_T>& m1, double num) {
    Matrix<_T> result(m1);
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = static_cast<_T>(result.data[index] + num);
    }
    return result;
}

template<typename _T>
Matrix<_T> operator-(const Matrix<_T>& m1, double num) {
    Matrix<_T> result(m1);
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = static_cast<_T>(result.data[index] - num);
    }
    return result;
}

template<typename _T>
Matrix<_T> operator/(const Matrix<_T>& m1, double num) {
    if (std::fabs(num) <= Matrix<_T>::doubleEpsilon) {
        throw MatrixException("Arithmetic error: division by zero is not allowed.");
    }
    Matrix<_T> result(m1);
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = static_cast<_T>(result.data[index] / num);
    }
    return result;
}

template<typename _T>
Matrix<_T> operator*(const Matrix<_T>& m1, double num) {
    Matrix<_T> result(m1);
    const unsigned int size = result.getStorageSize();
    for (unsigned int index = 0; index < size; ++index) {
        result.data[index] = static_cast<_T>(result.data[index] * num);
    }
    return result;
}

template<typename _T>
std::ostream& operator<<(std::ostream& os, const Matrix<_T>& matr) {
    for (unsigned int i = 0; i < matr.rows; ++i) {
        for (unsigned int j = 0; j < matr.columns; ++j) {
            os << matr.data[matr.getLinearIndex(i, j)] << " ";
        }
        os << "\n";
    }
    return os;
}

template<typename T>
Iterator<T> Matrix<T>::iterator_begin() {
    return Iterator<T>(*this);
}

template<typename T>
Iterator<T> Matrix<T>::iterator_end() {
    return Iterator<T>(*this, getStorageSize());
}

#endif // MATRIX_H
