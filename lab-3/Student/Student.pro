TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    student.cpp \
    studentlinux.cpp \
    studentwindows.cpp

HEADERS += \
    student.h \
    studentlinux.h \
    studentwindows.h

