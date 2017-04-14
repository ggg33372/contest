#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T17:04:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Contest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    activespectator.cpp \
    artist.cpp \
    wizardpages.cpp

HEADERS  += mainwindow.h \
    activespectator.h \
    artist.h \
    wizardpages.h

FORMS    += mainwindow.ui
