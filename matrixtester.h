#ifndef MATRIXTESTER_H
#define MATRIXTESTER_H

#include <string>
#include "outputPrinter.h"

class MatrixTester {
public:
    void runAllTests(OutputPrinter& output) const;

private:
    void testConstructor(OutputPrinter& output) const;
    void testCopyConstructor(OutputPrinter& output) const;
    void testMoveConstructor(OutputPrinter& output) const;
    void testInitializerListConstructor(OutputPrinter& output) const;
    void testAssignment(OutputPrinter& output) const;
    void testPlusEqual(OutputPrinter& output) const;
    void testMinusEqual(OutputPrinter& output) const;
    void testPlusMatrix(OutputPrinter& output) const;
    void testMinusMatrix(OutputPrinter& output) const;
    void testMultiplyMatrix(OutputPrinter& output) const;
    void testPlusNumber(OutputPrinter& output) const;
    void testMinusNumber(OutputPrinter& output) const;
    void testMultiplyNumber(OutputPrinter& output) const;
    void testDivideNumber(OutputPrinter& output) const;
    void testSetAndGet(OutputPrinter& output) const;
    void testRoundBracketsOperator(OutputPrinter& output) const;
    void testSquareCheck(OutputPrinter& output) const;
    void testRowsAndColumns(OutputPrinter& output) const;
    void testIterator(OutputPrinter& output) const;
    void testExceptions(OutputPrinter& output) const;

    void printTestPassed(OutputPrinter& output, const std::string& testName) const;
    void assertTrue(bool condition, const std::string& errorMessage) const;
};

#endif
