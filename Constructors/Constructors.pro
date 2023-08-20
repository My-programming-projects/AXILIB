include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SOURCES += \
        main.cpp 
        tst_constructors.cpp

INCLUDEPATH += C:\Projekty\Programowanie\AXILIB-master
DEPENDPATH += C:\Projekty\Programowanie\AXILIB-master
