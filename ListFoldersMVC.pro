#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T09:26:55
#
#-------------------------------------------------

QT       += core gui sql

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
    Models/testbase.cpp \
    Models/modelfunctions.cpp \
    Models/testthread.cpp \
    Models/modelobserver.cpp \
    Models/database.cpp \
    Views/treeviewer.cpp \
    Views/dialog.cpp \
    Controllers/treeviewercontroller.cpp \
    Models/treeviewermodel.cpp \
    Models/treemodel.cpp \
    Models/objecttreemodel.cpp \
    Views/test.cpp \
    Views/testtreemodel.cpp \
    Views/tn.cpp \
    Views/tnmodel.cpp

HEADERS  += mainwindow.h \
    Views/mainwindow.h \
    Controllers/controller.h \
    Models/model.h \
    Models/scandirectory.h \
    Views/functions.h \
    Models/Tree/dirnode.h \
    Models/Tree/filenode.h \
    Models/Tree/treenode.h \
    Models/testbase.h \
    Models/modelfunctions.h \
    Models/testthread.h \
    Models/modelobserver.h \
    Models/database.h \
    Views/treeviewer.h \
    Views/dialog.h \
    Controllers/treeviewercontroller.h \
    Models/treeviewermodel.h \
    Models/treemodel.h \
    Models/objecttreemodel.h \
    Views/test.h \
    Views/testtreemodel.h \
    Views/tn.h \
    Views/tnmodel.h

FORMS    += Views/mainwindow.ui \
    Views/treeviewer.ui \
    Views/dialog.ui

QMAKE_CXXFLAGS += -std=c++11
