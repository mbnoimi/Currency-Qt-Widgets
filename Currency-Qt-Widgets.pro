#-------------------------------------------------
#
# Project created by QtCreator 2017-07-08T11:08:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Currency-Qt-Widgets
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    currency/currency.cpp \
    currency/currencyinfo.cpp \
    currency/currencyinfodir.cpp \
    currency/currencylabel.cpp \
    currency/currencylineedit.cpp \
    currencydemo.cpp

HEADERS += \
    currency/currency.h \
    currency/currencyinfo.h \
    currency/currencyinfodir.h \
    currency/currencylabel.h \
    currency/currencylineedit.h \
    currency/currencywidgetsdef.h \
    currencydemo.h

DISTFILES += \
    README.md \
    LICENSE \
    README.md \
    LICENSE
