#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "inputReader.h"
#include "outputPrinter.h"
#include "matrixtester.h"

class AppController {
    private:
        const int menuExitValue = 0;
        const int menuRunTestsValue = 1;
        const int menuShowDemoValue = 2;
        const int menuMinValue = 0;
        const int menuMaxValue = 2;
        void processMenuChoice(int choice);
        void runTests();
        void showDemo();
        InputReader input;
        OutputPrinter output;
        MatrixTester tester;
    public:
        void run();
};

#endif // APPCONTROLLER_H
