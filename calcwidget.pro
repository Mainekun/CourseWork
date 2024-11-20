CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20

QT += core widgets gui

SOURCES += \
    Lexer.cpp \
    Parser.cpp \
    interpreter.cpp \
    main.cpp \
    mainwindow.cpp \
    vectorLib/vector.cpp \
    vectorLib/vectorexceptions.cpp \
    vectorLib/vectoriterator.cpp \
    vectorLib/vectormath.cpp \
    vectorlistmodel.cpp


TARGET = main.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    Lexer.h \
    Parser.h \
    interpreter.h \
    mainwindow.h \
    vectorLib/vector.h \
    vectorlistmodel.h
