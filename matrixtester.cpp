#include "matrixtester.h"
#include "outputPrinter.h"
#include "matrix.h"

#include <exception>
#include <sstream>
#include <utility>

void MatrixTester::runAllTests(OutputPrinter& output) const {
    int passedCount = 0;
    int failedCount = 0;

    runSingleTest(output, "constructor", &MatrixTester::testConstructor, passedCount, failedCount);
    runSingleTest(output, "copy constructor", &MatrixTester::testCopyConstructor, passedCount, failedCount);
    runSingleTest(output, "move constructor", &MatrixTester::testMoveConstructor, passedCount, failedCount);
    runSingleTest(output, "initializer list constructor", &MatrixTester::testInitializerListConstructor, passedCount, failedCount);
    runSingleTest(output, "assignment", &MatrixTester::testAssignment, passedCount, failedCount);
    runSingleTest(output, "operator +=", &MatrixTester::testPlusEqual, passedCount, failedCount);
    runSingleTest(output, "operator -=", &MatrixTester::testMinusEqual, passedCount, failedCount);
    runSingleTest(output, "operator +", &MatrixTester::testPlusMatrix, passedCount, failedCount);
    runSingleTest(output, "operator -", &MatrixTester::testMinusMatrix, passedCount, failedCount);
    runSingleTest(output, "operator * matrix", &MatrixTester::testMultiplyMatrix, passedCount, failedCount);
    runSingleTest(output, "operator + number", &MatrixTester::testPlusNumber, passedCount, failedCount);
    runSingleTest(output, "operator - number", &MatrixTester::testMinusNumber, passedCount, failedCount);
    runSingleTest(output, "operator * number", &MatrixTester::testMultiplyNumber, passedCount, failedCount);
    runSingleTest(output, "operator / number", &MatrixTester::testDivideNumber, passedCount, failedCount);
    runSingleTest(output, "set/get", &MatrixTester::testSetAndGet, passedCount, failedCount);
    runSingleTest(output, "operator()", &MatrixTester::testRoundBracketsOperator, passedCount, failedCount);
    runSingleTest(output, "is_square", &MatrixTester::testSquareCheck, passedCount, failedCount);
    runSingleTest(output, "rows and columns", &MatrixTester::testRowsAndColumns, passedCount, failedCount);
    runSingleTest(output, "iterator", &MatrixTester::testIterator, passedCount, failedCount);
    runSingleTest(output, "exceptions", &MatrixTester::testExceptions, passedCount, failedCount);

    output.printMessage("Passed: " + std::to_string(passedCount));
    output.printMessage("Failed: " + std::to_string(failedCount));
}

void MatrixTester::runSingleTest(
    OutputPrinter& output,
    const std::string& testName,
    void (MatrixTester::*testFunction)() const,
    int& passedCount,
    int& failedCount
    ) const {
    try {
        (this->*testFunction)();
        ++passedCount;
        output.printMessage("[OK] " + testName);
    } catch (const std::exception& ex) {
        ++failedCount;
        output.printMessage("[FAIL] " + testName + ": " + ex.what());
    }
}

void MatrixTester::testConstructor() const {
    Matrix<int> matrix(2, 3);

    assertTrue(matrix.get_row() == 2, "wrong row count");
    assertTrue(matrix.get_columns() == 3, "wrong column count");
    assertTrue(!matrix.is_square(), "matrix should not be square");
}

void MatrixTester::testCopyConstructor() const {
    Matrix<int> source{{1, 2}, {3, 4}};
    Matrix<int> copy(source);

    assertTrue(copy.get_elem(0, 0) == 1, "wrong element [0][0]");
    assertTrue(copy.get_elem(1, 1) == 4, "wrong element [1][1]");
}

void MatrixTester::testMoveConstructor() const {
    Matrix<int> source{{5, 6}, {7, 8}};
    Matrix<int> moved(std::move(source));

    assertTrue(moved.get_elem(0, 0) == 5, "wrong element [0][0]");
    assertTrue(moved.get_elem(1, 1) == 8, "wrong element [1][1]");
}

void MatrixTester::testInitializerListConstructor() const {
    Matrix<int> matrix{{10, 20}, {30, 40}};

    assertTrue(matrix.get_elem(0, 1) == 20, "wrong element [0][1]");
    assertTrue(matrix.get_elem(1, 0) == 30, "wrong element [1][0]");
}

void MatrixTester::testAssignment() const {
    Matrix<int> left(2, 2);
    Matrix<int> right{{7, 8}, {9, 10}};
    left = right;

    assertTrue(left.get_elem(0, 0) == 7, "wrong element [0][0]");
    assertTrue(left.get_elem(1, 1) == 10, "wrong element [1][1]");
}

void MatrixTester::testPlusEqual() const {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{10, 20}, {30, 40}};
    left += right;

    assertTrue(left.get_elem(0, 0) == 11, "wrong element [0][0]");
    assertTrue(left.get_elem(1, 1) == 44, "wrong element [1][1]");
}

void MatrixTester::testMinusEqual() const {
    Matrix<int> left{{10, 20}, {30, 40}};
    Matrix<int> right{{1, 2}, {3, 4}};
    left -= right;

    assertTrue(left.get_elem(0, 0) == 9, "wrong element [0][0]");
    assertTrue(left.get_elem(1, 1) == 36, "wrong element [1][1]");
}

void MatrixTester::testPlusMatrix() const {
    Matrix<int> left{{1, 2}, {3, 4}};
    Matrix<int> right{{5, 6}, {7, 8}};
    Matrix<int> result = left + right;

    assertTrue(result.get_elem(0, 0) == 6, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 12, "wrong element [1][1]");
}

void MatrixTester::testMinusMatrix() const {
    Matrix<int> left{{10, 20}, {30, 40}};
    Matrix<int> right{{1, 2}, {3, 4}};
    Matrix<int> result = left - right;

    assertTrue(result.get_elem(0, 0) == 9, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 36, "wrong element [1][1]");
}

void MatrixTester::testMultiplyMatrix() const {
    Matrix<int> left{{1, 2, 3}, {4, 5, 6}};
    Matrix<int> right{{7, 8}, {9, 10}, {11, 12}};
    Matrix<int> result = left * right;

    assertTrue(result.get_row() == 2, "wrong result row count");
    assertTrue(result.get_columns() == 2, "wrong result column count");
    assertTrue(result.get_elem(0, 0) == 58, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 154, "wrong element [1][1]");
}

void MatrixTester::testPlusNumber() const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Matrix<int> result = matrix + 2.0;

    assertTrue(result.get_elem(0, 0) == 3, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 6, "wrong element [1][1]");
}

void MatrixTester::testMinusNumber() const {
    Matrix<int> matrix{{5, 6}, {7, 8}};
    Matrix<int> result = matrix - 2.0;

    assertTrue(result.get_elem(0, 0) == 3, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 6, "wrong element [1][1]");
}

void MatrixTester::testMultiplyNumber() const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Matrix<int> result = matrix * 3.0;

    assertTrue(result.get_elem(0, 0) == 3, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 12, "wrong element [1][1]");
}

void MatrixTester::testDivideNumber() const {
    Matrix<int> matrix{{10, 20}, {30, 40}};
    Matrix<int> result = matrix / 10.0;

    assertTrue(result.get_elem(0, 0) == 1, "wrong element [0][0]");
    assertTrue(result.get_elem(1, 1) == 4, "wrong element [1][1]");
}

void MatrixTester::testSetAndGet() const {
    Matrix<int> matrix(2, 2);
    matrix.set_elem(1, 0, 77);

    assertTrue(matrix.get_elem(1, 0) == 77, "wrong element [1][0]");
}

void MatrixTester::testRoundBracketsOperator() const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    matrix(0, 1) = 100;

    assertTrue(matrix.get_elem(0, 1) == 100, "wrong element [0][1]");
}

void MatrixTester::testSquareCheck() const {
    Matrix<int> square(2, 2);
    Matrix<int> rectangle(2, 3);

    assertTrue(square.is_square(), "square matrix was not recognized");
    assertTrue(!rectangle.is_square(), "rectangle matrix was recognized as square");
}

void MatrixTester::testRowsAndColumns() const {
    Matrix<int> matrix(3, 4);

    assertTrue(matrix.get_row() == 3, "wrong row count");
    assertTrue(matrix.get_columns() == 4, "wrong column count");
}

void MatrixTester::testIterator() const {
    Matrix<int> matrix{{1, 2}, {3, 4}};
    Iterator<int> iterator = matrix.iterator_begin();
    Iterator<int> endIterator = matrix.iterator_end();
    int sum = 0;

    while (iterator != endIterator) {
        sum += *iterator;
        ++iterator;
    }

    assertTrue(sum == 10, "wrong traversal sum");
}

void MatrixTester::testExceptions() const {
    bool sizeExceptionCaught = false;
    bool indexExceptionCaught = false;
    bool divisionExceptionCaught = false;
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
        Matrix<int> result = matrix / 0.0;
        (void)result;
    } catch (const MatrixException&) {
        divisionExceptionCaught = true;
    }

    try {
        Matrix<int> matrix{{1, 2}, {3, 4}};
        Iterator<int> iterator = matrix.iterator_end();
        iterator.value();
    } catch (const MatrixIteratorException&) {
        iteratorExceptionCaught = true;
    }

    assertTrue(sizeExceptionCaught, "size exception was not thrown");
    assertTrue(indexExceptionCaught, "index exception was not thrown");
    assertTrue(divisionExceptionCaught, "division exception was not thrown");
    assertTrue(iteratorExceptionCaught, "iterator exception was not thrown");
}

void MatrixTester::assertTrue(bool condition, const std::string& errorMessage) {
    if (!condition) {
        throw std::runtime_error(errorMessage);
    }
}
