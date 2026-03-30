#include "outputPrinter.h"
#include <iostream>

void OutputPrinter::printMainMenu() const {
    std::cout << "Menu:\n";
    std::cout << "0 - Exit\n";
    std::cout << "1 - Run tests\n";
    std::cout << "2 - Show demo\n";
}

void OutputPrinter::printMessage(const std::string& message) const {
    std::cout << message << "\n";
}

void OutputPrinter::printError(const std::string& errorMessage) const {
    std::cout << "Error: " << errorMessage << "\n";
}
