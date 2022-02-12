include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SOURCES += \
        main.cpp         tst_mt.cpp


INCLUDEPATH += D:\Matrix_library\AXI-Matrix-master(1)\AXI-Matrix-master
DEPENDPATH += D:\Matrix_library\AXI-Matrix-master(1)\AXI-Matrix-master
