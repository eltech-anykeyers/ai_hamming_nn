QT += core gui widgets

TARGET = AIB_Seven
TEMPLATE = app

CONFIG += c++1z
QMAKE_CXXFLAGS += -std=c++1z

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        window.cpp

HEADERS += \
        window.hpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
