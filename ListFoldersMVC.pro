#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T09:26:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MVC
TEMPLATE = app


SOURCES += main.cpp\
    Views/mainwindow.cpp \
    Controllers/controller.cpp \
    Models/model.cpp \
    Models/scandirectory.cpp

HEADERS  += mainwindow.h \
    Views/mainwindow.h \
    Controllers/controller.h \
    Models/model.h \
    Models/scandirectory.h

FORMS    += Views/mainwindow.ui
