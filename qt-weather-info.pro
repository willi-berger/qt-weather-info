#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T12:08:27
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core network

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    getweatherasjson.cpp \
    weatherinfo.cpp

HEADERS  += mainwindow.h \
    getweatherasjson.h \
    weatherinfo.h

FORMS    += mainwindow.ui


INCLUDEPATH += /usr/include/qjson
LIBS += -Lf/usr/include/qjson/ -lqjson
