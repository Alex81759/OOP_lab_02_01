#include "matrixTester.h"
#include "matrix.h"
#include <utility>
#include <exception>

void MatrixTester::runAllTests(OutputPrinter& output) const {
    testConstructor(output);
    testCopyConstructor(output);
    testMoveConstructor(output);
    testInitializerListConstructor(output);
    testAssignment(output);
    testPlusEqual(output);
    testMinusEqual(output);
    testPlusMatrix(output);
    testMinusMatrix(output);
    testMultiplyMatrix(output);
    testPlusNumber(output);
    testMinusNumber(output);
    testMultiplyNumber(output);
    testDivideNumber(output);
    testSetAndGet(output);
    testRoundBracketsOperator(output);
    testSquareCheck(output);
    testRowsAndColumns(output);
    testIterator(output);
    testExceptions(output);
    output.printMessage("All tests completed.");
}

void MatrixTester::testConstructor(OutputPrinter& output) const {
    Matrix<int> matrix(2, 3);
    assertTrue(matrix.get_row() == 2, "Constructor test failed: wrong row count.");
    assertTrue(matrix.get_columns() == 3, "Constructor test failed: wrong column count.");
    printTestPassed(output, "Constructor");
}

void MatrixTester::testCopyConstructor(OutputPrinter& output) const {
    Matrix<int> source{{1, 2}, {3, 4}};
    Matrix<int> copy(source);

    assertTrue(copy.get_elem(0, 0) == 1, "Copy constructor test failed: wrong element [0][0].");
    assertTrue(copy.get_elem(1, 1) == 4, "Copy constructor test failed: wrong element [1][1].");
    printTestPassed(output, "Copy constructor");
}

void MatrixTester::testMoveConstructor(OutputPrinter& output) const {
    Matrix<int> source{{1, 2}, {3, 4}};
    Matrix<int> moved(std::move(source));

    assertTrue(moved.get_elem(0, 0) == 1, "Move constructor test failed: wrong element [0][0].");
    assertTrue(moved.get_elem(1, 1) == 4, "Move constructor test failed: wrong element [1][1].");
    printTestPassed(output, "Move constructor");
}

void MatrixTester::testInitializerListConstructor(OutputPrinter& output) const {
    Matrix<int> matrix{{10, 20}, {30, 40}};
    assertTrue(matrix.get_elem(0, 1) == 20, "Initializer list test failed: wrong element [0][1].");
    assertTrue(matrix.get_elem(1, 0) == 30, "Initializer list test failed: wrong element [1][0].");
    printTestPassed(output, "Initializer list constructor");
}

void MatrixTester::testAssignment(OutputPrinter& output) const {
    Matrix<int> left(2, 2);
    Matrix<int> right{{7, 8}, {9, 10}};
    left = right;

    assertTrue(left.get_elem(0, 0) == 7, "Assignment test failed: wrong element [0][0].");
    assertTrue(left.get_elem(1, 1) == 10, "Assignment test failed: wrong element [1][1].");
    printTestPassed(output, "Assignment");
}

void MatrixTester::testPlusEqual(OutputPrinter& output) const {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{10, 20}, {30, 40}};
    left += right;

    assertTrue(left.get_elem(0, 0) == 11, "Operator += test failed: wrong element [0][0].");
    assertTrue(left.get_elem(1, 1) == 44, "Operator += test failed: wrong element [1][1].");
    printTestPassed(output, "Operator +=");
}

void MatrixTester::testMinusEqual(OutputPrinter& output) const {
    Matrix<int> left{{10, 20}, {30, 40}};
    Matrix<int> right{{1, 2}, {3, 4}};
    left -= right;

    assertTrue(left.get_elem(0, 0) == 9, "Operator -= test failed: wrong element [0][0].");
    assertTrue(left.get_elem(1, 1) == 36, "Operator -= test failed: wrong element [1][1].");
    printTestPassed(output, "Operator -=");
}

void MatrixTester::testPlusMatrix(OutputPrinter& output) const {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{5, 6}, {7, 8}};
    Matrix<int> result = left + right;

    assertTrue(result.get_elem(0, 0) == 6, "Operator + test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 12, "Operator + test failed: wrong element [1][1].");
    printTestPassed(output, "Operator +");
}

void MatrixTester::testMinusMatrix(OutputPrinter& output) const {
    Matrix<int> left{{10, 20}, {30, 40}};
    Matrix<int> right{{1, 2}, {3, 4}};
    Matrix<int> result = left - right;

    assertTrue(result.get_elem(0, 0) == 9, "Operator - test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 36, "Operator - test failed: wrong element [1][1].");
    printTestPassed(output, "Operator -");
}

void MatrixTester::testMultiplyMatrix(OutputPrinter& output) const {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{5, 6}, {7, 8}};
    Matrix<int> result = left * right;

    assertTrue(result.get_elem(0, 0) == 19, "Operator * matrix test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 50, "Operator * matrix test failed: wrong element [1][1].");
    printTestPassed(output, "Operator * matrix");
}

void MatrixTester::testPlusNumber(OutputPrinter& output) const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Matrix<int> result = matrix + 2.0;

    assertTrue(result.get_elem(0, 0) == 3, "Operator + number test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 6, "Operator + number test failed: wrong element [1][1].");
    printTestPassed(output, "Operator + number");
}

void MatrixTester::testMinusNumber(OutputPrinter& output) const {
    Matrix<int> matrix{{5, 6}, {7, 8}};
    Matrix<int> result = matrix - 2.0;

    assertTrue(result.get_elem(0, 0) == 3, "Operator - number test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 6, "Operator - number test failed: wrong element [1][1].");
    printTestPassed(output, "Operator - number");
}

void MatrixTester::testMultiplyNumber(OutputPrinter& output) const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Matrix<int> result = matrix * 3.0;

    assertTrue(result.get_elem(0, 0) == 3, "Operator * number test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 12, "Operator * number test failed: wrong element [1][1].");
    printTestPassed(output, "Operator * number");
}

void MatrixTester::testDivideNumber(OutputPrinter& output) const {
    Matrix<int> matrix{{10, 20}, {30, 40}};
    Matrix<int> result = matrix / 10.0;

    assertTrue(result.get_elem(0, 0) == 1, "Operator / number test failed: wrong element [0][0].");
    assertTrue(result.get_elem(1, 1) == 4, "Operator / number test failed: wrong element [1][1].");
    printTestPassed(output, "Operator / number");
}

void MatrixTester::testSetAndGet(OutputPrinter& output) const {
    Matrix<int> matrix(2, 2);
    matrix.set_elem(1, 0, 77);

    assertTrue(matrix.get_elem(1, 0) == 77, "Set/Get test failed: wrong element [1][0].");
    printTestPassed(output, "set_elem and get_elem");
}

void MatrixTester::testRoundBracketsOperator(OutputPrinter& output) const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    matrix(0, 1) = 100;

    assertTrue(matrix.get_elem(0, 1) == 100, "Operator() test failed: wrong element [0][1].");
    printTestPassed(output, "Operator()");
}

void MatrixTester::testSquareCheck(OutputPrinter& output) const {
    Matrix<int> square(2, 2);
    Matrix<int> rectangle(2, 3);

    assertTrue(square.is_square(), "is_square test failed: square matrix was not recognized.");
    assertTrue(!rectangle.is_square(), "is_square test failed: rectangle matrix was recognized as square.");
    printTestPassed(output, "is_square");
}

void MatrixTester::testRowsAndColumns(OutputPrinter& output) const {
    Matrix<int> matrix(3, 4);

    assertTrue(matrix.get_row() == 3, "get_row test failed: wrong row count.");
    assertTrue(matrix.get_columns() == 4, "get_columns test failed: wrong column count.");
    printTestPassed(output, "get_row and get_columns");
}

void MatrixTester::testIterator(OutputPrinter& output) const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Iterator<int> iterator = matrix.iterator_begin();
    Iterator<int> endIterator = matrix.iterator_end();
    int sum = 0;

    while (iterator != endIterator) {
        sum += *iterator;
        ++iterator;
    }

    assertTrue(sum == 10, "Iterator test failed: wrong traversal sum.");
    printTestPassed(output, "Iterator");
}

void MatrixTester::testExceptions(OutputPrinter& output) const {
    bool sizeExceptionCaught = false;
    bool indexExceptionCaught = false;
    bool iteratorExceptionCaught = false;

    try {
        Matrix<int> left(2, 2);
        Matrix<int> right(3, 3);
        Matrix<int> result = left + right;
        (void)result;
    } catch (const MatrixSizeException&) {
        sizeExceptionCaught = true;
    }

    try {
        Matrix<int> matrix(2, 2);
        matrix.get_elem(10, 10);
    } catch (const MatrixIndexException&) {
        indexExceptionCaught = true;
    }

    try {
        Matrix<int> matrix{{1, 2}, {3, 4}};
        Iterator<int> iterator = matrix.iterator_end();
        iterator.value();
    } catch (const MatrixIteratorException&) {
        iteratorExceptionCaught = true;
    }

    assertTrue(sizeExceptionCaught, "Exception test failed: size exception was not thrown.");
    assertTrue(indexExceptionCaught, "Exception test failed: index exception was not thrown.");
    assertTrue(iteratorExceptionCaught, "Exception test failed: iterator exception was not thrown.");
    printTestPassed(output, "Exceptions");
}

void MatrixTester::printTestPassed(OutputPrinter& output, const std::string& testName) const {
    output.printMessage(testName + " test passed.");
}

void MatrixTester::assertTrue(bool condition, const std::string& errorMessage) const {
    if (!condition) {
        throw std::runtime_error(errorMessage);
    }
}
