#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T00:51:40
#
#-------------------------------------------------

QT       += core gui sql network webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LollyQt
TEMPLATE = app

CONFIG += c++11

INCLUDEPATH += C:/zw/boost_1_61_0

SOURCES += main.cpp\
        mainwindow.cpp \
    lollydb.cpp \
    selectunitsdialog.cpp \
    wordsonlinedialog.cpp \
    wordsonlineviewmodel.cpp \
    selectunitsviewmodel.cpp

HEADERS  += mainwindow.h \
    lollydb.h \
    selectunitsdialog.h \
    wordsonlinedialog.h \
    wordsonlineviewmodel.h \
    selectunitsviewmodel.h

FORMS    += mainwindow.ui \
    selectunitsdialog.ui \
    wordsonlinedialog.ui
