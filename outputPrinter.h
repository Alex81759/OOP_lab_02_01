#ifndef OUTPUTPRINTER_H
#define OUTPUTPRINTER_H

#include <iostream>
#include <string>
#include "matrix.h"

class OutputPrinter {
public:
    void printMainMenu() const;
    void printMessage(const std::string& message) const;
    void printError(const std::string& errorMessage) const;

    template<typename T>
    void printMatrix(const Matrix<T>& matrix) const {
        printMessage("--------------------");
        std::cout << matrix;
        printMessage("--------------------");
    }
};

#endif // OUTPUTPRINTER_H
