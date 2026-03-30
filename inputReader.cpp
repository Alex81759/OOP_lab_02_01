#include "inputReader.h"
#include <iostream>
#include <limits>

int InputReader::readMenuChoice(int minValue, int maxValue) const {
    int value = 0;
    bool isValid = false;

    while (!isValid) {
        std::cout << "Choose menu item [" << minValue << ".." << maxValue << "]: ";
        std::cin >> value;

        isValid = isChoiceValid(value, minValue, maxValue);
        if (!isValid) {
            std::cout << "Invalid input. Try again.\n";
        }

        clearInput();
    }

    return value;
}

void InputReader::clearInput() const {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool InputReader::isChoiceValid(int value, int minValue, int maxValue) const {
    return std::cin.good() && value >= minValue && value <= maxValue;
}
