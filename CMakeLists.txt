cmake_minimum_required(VERSION 3.16)

project(OOP_lab_02_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OOP_lab_02_01 main.cpp

    matrixExceptions.h

    inputReader.h inputReader.cpp
    outputPrinter.h outputPrinter.cpp
    appController.h appController.cpp

    matrixTester.h matrixTester.cpp
    matrix.h
    matrixIterator.h
)

include(GNUInstallDirs)
install(TARGETS OOP_lab_02_01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
