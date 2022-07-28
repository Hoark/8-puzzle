TEMPLATE = app
TARGET = 8_puzzle

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES +=  main.cpp \
    mainwindow.cpp \
    node.cpp \
    solve.cpp

HEADERS += \
    mainwindow.h \
    node.h \
    solve.h
