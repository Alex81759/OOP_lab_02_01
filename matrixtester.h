#ifndef MATRIXTESTER_H
#define MATRIXTESTER_H

#include <string>

class OutputPrinter;

class MatrixTester {
public:
    void runAllTests(OutputPrinter& output) const;

private:
    void runSingleTest(
        OutputPrinter& output,
        const std::string& testName,
        void (MatrixTester::*testFunction)() const,
        int& passedCount,
        int& failedCount
        ) const;

    void testConstructor() const;
    void testCopyConstructor() const;
    void testMoveConstructor() const;
    void testInitializerListConstructor() const;
    void testAssignment() const;
    void testPlusEqual() const;
    void testMinusEqual() const;
    void testPlusMatrix() const;
    void testMinusMatrix() const;
    void testMultiplyMatrix() const;
    void testPlusNumber() const;
    void testMinusNumber() const;
    void testMultiplyNumber() const;
    void testDivideNumber() const;
    void testSetAndGet() const;
    void testRoundBracketsOperator() const;
    void testSquareCheck() const;
    void testRowsAndColumns() const;
    void testIterator() const;
    void testExceptions() const;

    static void assertTrue(bool condition, const std::string& errorMessage);
};

#endif // MATRIXTESTER_H
