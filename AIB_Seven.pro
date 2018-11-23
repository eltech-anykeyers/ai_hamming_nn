QT += core gui widgets

TARGET = AIB_Seven
TEMPLATE = app

CONFIG += c++14

SOURCES += \
        main.cpp \
        window.cpp \
        hamming.cpp \
        grid_drawer/grid_drawer.cpp \
        grid_drawer/marked_drawer.cpp

HEADERS += \
        window.hpp \
        hamming.hpp \
        grid_drawer/grid_drawer.hpp \
        grid_drawer/marked_drawer.hpp

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
