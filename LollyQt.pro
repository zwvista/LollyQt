#-------------------------------------------------
#
# Project created by QtCreator 2016-02-15T00:51:40
#
#-------------------------------------------------

QT       += core gui sql network webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LollyQt
TEMPLATE = app

CONFIG += c++17

INCLUDEPATH += /usr/local/Cellar/cpprestsdk/2.10.13/include \
    /usr/local/Cellar/boost/1.69.0_2/include \
    /usr/local/Cellar/libressl/2.8.3/include\
    /usr/local/Cellar/nlohmann_json/3.6.1/include \
    /Users/zhaowei/Documents/Programs/OSS/RxCpp/Rx/v2/src

LIBS += -L/usr/local/Cellar/cpprestsdk/2.10.13/lib \
    -L/usr/local/Cellar/boost/1.69.0_2/lib \
    -L/usr/local/Cellar/libressl/2.8.3/lib \
    -lcpprest -lboost_system -lboost_thread-mt -lboost_chrono-mt -lssl -lcrypto

SOURCES += main.cpp \
    Models/mautocorrect.cpp \
    Models/mdictionary.cpp \
    Models/mlangphrase.cpp \
    Models/mlangword.cpp \
    Models/mtextbook.cpp \
    Models/munitphrase.cpp \
    Models/munitword.cpp \
    Models/mvoice.cpp \
    Models/mwordfami.cpp \
    Services/sautocorrect.cpp \
    Services/sdictionary.cpp \
    Services/slangphrase.cpp \
    Services/slangword.cpp \
    Services/stextbook.cpp \
    Services/sunitphrase.cpp \
    Services/sunitword.cpp \
    Services/svoice.cpp \
    mainwindow.cpp \
    lollydb.cpp \
    selectunitsdialog.cpp \
    Services/swordfami.cpp \
    wordsonlinedialog.cpp \
    wordsonlineviewmodel.cpp \
    selectunitsviewmodel.cpp

HEADERS  += mainwindow.h \
    Helpers/optional2json.h \
    Helpers/restapi.h \
    Helpers/rx.h \
    Models/mautocorrect.h \
    Models/mcommon.h \
    Models/mdictionary.h \
    Models/mlangphrase.h \
    Models/mlangword.h \
    Models/mtextbook.h \
    Models/munitphrase.h \
    Models/munitword.h \
    Models/mvoice.h \
    Models/mwordfami.h \
    Services/sautocorrect.h \
    Services/sdictionary.h \
    Services/slangphrase.h \
    Services/slangword.h \
    Services/stextbook.h \
    Services/sunitphrase.h \
    Services/sunitword.h \
    Services/svoice.h \
    lollydb.h \
    selectunitsdialog.h \
    Services/swordfami.h \
    wordsonlinedialog.h \
    wordsonlineviewmodel.h \
    selectunitsviewmodel.h

FORMS    += mainwindow.ui \
    selectunitsdialog.ui \
    wordsonlinedialog.ui
