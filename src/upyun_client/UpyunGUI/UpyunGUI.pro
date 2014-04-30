#-------------------------------------------------
#
# Project created by QtCreator 2014-04-29T14:37:34
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = UpyunGUI
TEMPLATE = app



SOURCES += main.cpp\
        widget.cpp \
    ../upyun_client.cpp \
    ../upyun_client_impl.cpp \
    dialoglogin.cpp

HEADERS  += widget.h \
    ../upyun_client.h \
    ../upyun_client_impl.h \
    dialoglogin.h

FORMS    += widget.ui \
    dialoglogin.ui
