#ifndef MATRIXEXCEPTIONS_H
#define MATRIXEXCEPTIONS_H

#include <stdexcept>
#include <string>

class MatrixException : public std::runtime_error {
public:
    explicit MatrixException(const std::string& message)
        : std::runtime_error(message) {
    }
};

class MatrixIndexException : public MatrixException {
public:
    explicit MatrixIndexException(const std::string& message)
        : MatrixException(message) {
    }
};

class MatrixSizeException : public MatrixException {
public:
    explicit MatrixSizeException(const std::string& message)
        : MatrixException(message) {
    }
};

class MatrixMemoryException : public MatrixException {
public:
    explicit MatrixMemoryException(const std::string& message)
        : MatrixException(message) {
    }
};

class MatrixIteratorException : public MatrixException {
public:
    explicit MatrixIteratorException(const std::string& message)
        : MatrixException(message) {
    }
};

#endif // MATRIXEXCEPTIONS_H
