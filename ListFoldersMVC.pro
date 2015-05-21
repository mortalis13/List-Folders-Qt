#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T09:26:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ListFoldersMVC
TEMPLATE = app


SOURCES += main.cpp\
    Views/mainwindow.cpp \
    Controllers/controller.cpp \
    Models/model.cpp \
    Models/scandirectory.cpp \
    Views/functions.cpp \
    Models/Tree/dirnode.cpp \
    Models/Tree/filenode.cpp \
    Models/Tree/treenode.cpp \
    Models/test.cpp \
    Models/testbase.cpp \
    Models/modelfunctions.cpp

HEADERS  += mainwindow.h \
    Views/mainwindow.h \
    Controllers/controller.h \
    Models/model.h \
    Models/scandirectory.h \
    Views/functions.h \
    Models/Tree/dirnode.h \
    Models/Tree/filenode.h \
    Models/Tree/treenode.h \
    Models/test.h \
    Models/testbase.h \
    Models/modelfunctions.h

FORMS    += Views/mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
