TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    src/timer.cpp \
    src/timeruser.cpp

INCLUDEPATH += \
    headers

HEADERS += \
    headers/timer.h \
    headers/timeruser.h
