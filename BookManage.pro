#-------------------------------------------------
#
# Project created by QtCreator 2017-12-31T11:03:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookManage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    adddialog.cpp \
    borrowinfodialog.cpp \
    book.cpp \
    searchdialog.cpp \
    drawdialog.cpp

HEADERS  += mainwindow.h \
    adddialog.h \
    borrowinfodialog.h \
    BTree.h \
    searchdialog.h \
    drawdialog.h \
    Book.h

FORMS    += mainwindow.ui \
    adddialog.ui \
    borrowinfodialog.ui \
    searchdialog.ui \
    drawdialog.ui

DISTFILES += \
    icon.rc

RC_FILE = icon.rc
