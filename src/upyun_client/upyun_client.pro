#-------------------------------------------------
#
# Project created by QtCreator 2014-04-24T14:28:12
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = upyun_client
TEMPLATE = lib

DEFINES += UPYUN_CLIENT_LIBRARY

SOURCES += upyun_client.cpp \
    upyun_client_impl.cpp

HEADERS += upyun_client.h\
        upyun_client_global.h \
    upyun_client_impl.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
