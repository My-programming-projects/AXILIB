include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

SOURCES += \
        main.cpp         tst_itertests.cpp

INCLUDEPATH += D:\Projects\AXILIB-library\AXILIB
DEPENDPATH += D:\Projects\AXILIB-library\AXILIB
