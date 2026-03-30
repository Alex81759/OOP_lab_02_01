#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "inputReader.h"
#include "outputPrinter.h"
#include "matrixtester.h"

class AppController {
private:
    void processMenuChoice(int choice, bool& isRunning);
    void runTests();
    void showDemo();

    InputReader input;
    OutputPrinter output;
    MatrixTester tester;

public:
    void run();
};

#endif // APPCONTROLLER_H
