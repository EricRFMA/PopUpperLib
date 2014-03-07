#-------------------------------------------------
#
# Project created by QtCreator 2014-01-10T11:28:52
#
#-------------------------------------------------

QT       += widgets

TARGET = PopUpperLib
TEMPLATE = lib

DEFINES += POPUPPERLIB_LIBRARY

SOURCES += popupperlib.cpp \
    ../PopUpper/mainwindow.cpp \
    ../PopUpper/poppyupper.cpp \
    ../PopUpper/utilities.cpp

HEADERS += popupperlib.h\
        popupperlib_global.h \
    ../PopUpper/CSScolor.h \
    ../PopUpper/mainwindow.h \
    ../PopUpper/poppyupper.h \
    ../PopUpper/utilities.h \
    Runner.hpp

unix {
    target.path = /usr/local/lib
    INSTALLS += target
}

FORMS += \
    ../PopUpper/mainwindow.ui \
    ../PopUpper/poppyupper.ui
