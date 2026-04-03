#include "appController.h"
#include "matrix.h"
#include <exception>

void AppController::run() {
    bool isRunning = true;
    while (isRunning) {
        try {
            output.printMainMenu();
            const int choice = input.readMenuChoice(menuMinValue, menuMaxValue);
            if (choice == menuExitValue) {
                isRunning = false;
            } else {
                processMenuChoice(choice);
            }
        } catch (const std::exception& ex) {
            output.printError(ex.what());
        }
    }
}

void AppController::processMenuChoice(int choice) {
    if (choice == menuRunTestsValue) {
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
