#include "appController.h"
#include "matrix.h"
#include <exception>

namespace {
const int menuExitValue = 0;
const int menuRunTestsValue = 1;
const int menuShowDemoValue = 2;
const int menuMinValue = 0;
const int menuMaxValue = 2;
}

void AppController::run() {
    bool isRunning = true;
    while (isRunning) {
        try {
            output.printMainMenu();
            const int choice = input.readMenuChoice(menuMinValue, menuMaxValue);
            processMenuChoice(choice, isRunning);
        } catch (const std::exception& ex) {
            output.printError(ex.what());
        }
    }
}

void AppController::processMenuChoice(int choice, bool& isRunning) {
    if (choice == menuExitValue) {
        isRunning = false;
    } else if (choice == menuRunTestsValue) {
        runTests();
    } else {
        showDemo();
    }
}

void AppController::runTests() {
    tester.runAllTests(output);
}

void AppController::showDemo() {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{5, 6}, {7, 8}};
    Matrix<int> sum = left + right;
    Matrix<int> product = left * right;

    output.printMessage("Left matrix:");
    output.printMatrix(left);
    output.printMessage("Right matrix:");
    output.printMatrix(right);
    output.printMessage("Sum:");
    output.printMatrix(sum);
    output.printMessage("Product:");
    output.printMatrix(product);
}
