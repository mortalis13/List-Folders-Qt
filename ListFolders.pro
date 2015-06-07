#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T09:26:55
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ListFolders
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
    Models/modelfunctions.cpp \
    Models/modelobserver.cpp \
    Models/database.cpp \
    Views/treeviewer.cpp \
    Controllers/treeviewercontroller.cpp \
    Models/treeviewermodel.cpp \
    Models/treemodel.cpp \

HEADERS  += mainwindow.h \
    Views/mainwindow.h \
    Controllers/controller.h \
    Models/model.h \
    Models/scandirectory.h \
    Views/functions.h \
    Models/Tree/dirnode.h \
    Models/Tree/filenode.h \
    Models/Tree/treenode.h \
    Models/modelfunctions.h \
    Models/modelobserver.h \
    Models/database.h \
    Views/treeviewer.h \
    Controllers/treeviewercontroller.h \
    Models/treeviewermodel.h \
    Models/treemodel.h \

FORMS    += Views/mainwindow.ui \
    Views/treeviewer.ui \

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc

# RC_FILE = resources.rc
win32:RC_ICONS += icon.ico
