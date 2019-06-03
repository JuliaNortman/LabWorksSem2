QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console c++14

INCLUDEPATH += "../../"
INCLUDEPATH += "googletest"
INCLUDEPATH += "googletest/include"
INCLUDEPATH += "googlemock"
INCLUDEPATH += "googlemock/include"
INCLUDEPATH += "../../GraphAlgorithms/"

SOURCES += \
    main.cpp \
    ../../GraphAlgorithms/graph.cpp\
    ../../GraphAlgorithms/graph_algorithm.cpp \
    ../../writeinfile.cpp \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc

HEADERS += \
    ../../GraphAlgorithms/graph.h \
    ../../GraphAlgorithms/graph_algorithm.h \
    ../../writeinfile.h\
    main.h
