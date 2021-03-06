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

INCLUDEPATH += /usr/local/Cellar/cpprestsdk/2.10.16/include \
    /usr/local/Cellar/boost/1.74.0/include \
    /usr/local/Cellar/libressl/3.2.2/include\
    /usr/local/Cellar/nlohmann_json/3.9.1/include \
    /usr/local/Cellar/range-v3/0.11.0/include \
    /Users/zhaowei/Documents/Programs/OSS/RxCpp/Rx/v2/src \
    /Users/zhaowei/Documents/Programs/OSS/rxqt/include

LIBS += -L/usr/local/Cellar/cpprestsdk/2.10.16/lib \
    -L/usr/local/Cellar/boost/1.74.0/lib \
    -L/usr/local/Cellar/libressl/3.2.2/lib \
    -lcpprest -lboost_system -lboost_thread-mt -lboost_chrono-mt -lssl -lcrypto -lboost_regex

#QMAKE_CXXFLAGS += /std:c++17 /permissive- /Zc:preprocessor /bigobj

#INCLUDEPATH += C:\zw\vcpkg\installed\x86-windows\include\cpprest \
#    C:\zw\vcpkg\installed\x86-windows\include\boost \
#    C:\zw\vcpkg\installed\x86-windows\include\openssl \
#    C:\zw\vcpkg\installed\x86-windows\include\nlohmann \
#    C:\zw\range-v3\include \
#    C:\zw\vcpkg\installed\x86-windows\include\rxcpp \
#    C:\zw\vcpkg\installed\x86-windows\include

#LIBS += -LC:\zw\vcpkg\installed\x86-windows\lib \
#    -lcpprest_2_10 -lboost_system-vc140-mt -lboost_thread-vc140-mt -lboost_chrono-vc140-mt -llibssl -llibcrypto -lboost_regex-vc140-mt

#LIBS += -LC:\zw\vcpkg\installed\x86-windows\debug\lib \
#    -lcpprest_2_10d -lboost_system-vc140-mt-gd -lboost_thread-vc140-mt-gd -lboost_chrono-vc140-mt-gd -llibssl -llibcrypto -lboost_regex-vc140-mt-gd

SOURCES += main.cpp \
    Helpers/uri.cpp \
    Models/mautocorrect.cpp \
    Models/mdictionary.cpp \
    Models/mlangphrase.cpp \
    Models/mlanguage.cpp \
    Models/mlangword.cpp \
    Models/mtextbook.cpp \
    Models/munitphrase.cpp \
    Models/munitword.cpp \
    Models/musersetting.cpp \
    Models/musmapping.cpp \
    Models/mvoice.cpp \
    Models/mwordfami.cpp \
    Old/lollydb.cpp \
    Old/selectunitsdialog.cpp \
    Old/selectunitsviewmodel.cpp \
    Old/wordsonlinedialog.cpp \
    Old/wordsonlineviewmodel.cpp \
    Services/sautocorrect.cpp \
    Services/sdictionary.cpp \
    Services/slangphrase.cpp \
    Services/slanguage.cpp \
    Services/slangword.cpp \
    Services/stextbook.cpp \
    Services/sunitphrase.cpp \
    Services/sunitword.cpp \
    Services/susersetting.cpp \
    Services/susmapping.cpp \
    Services/svoice.cpp \
    Services/swordfami.cpp \
    Shared/commonapi.cpp \
    UI/mainwindow.cpp \
    UI/settingsdialog.cpp \
    UI/wordsunitwindow.cpp \
    ViewModels/vmsettings.cpp \
    ViewModels/vmwordsunit.cpp \
    UI/wordsunitwordsmodel.cpp

HEADERS  += mainwindow.h \
    Helpers/optional2json.h \
    Helpers/restapi.h \
    Helpers/rx.h \
    Helpers/string_t.h \
    Helpers/uri.h \
    Helpers/wstring2json.h \
    Models/mautocorrect.h \
    Models/mcommon.h \
    Models/mdictionary.h \
    Models/mlangphrase.h \
    Models/mlanguage.h \
    Models/mlangword.h \
    Models/mselectitem.h \
    Models/mtextbook.h \
    Models/munitphrase.h \
    Models/munitword.h \
    Models/musersetting.h \
    Models/musmapping.h \
    Models/mvoice.h \
    Models/mwordfami.h \
    Old/lollydb.h \
    Old/selectunitsdialog.h \
    Old/selectunitsviewmodel.h \
    Old/wordsonlinedialog.h \
    Old/wordsonlineviewmodel.h \
    Services/sautocorrect.h \
    Services/sdictionary.h \
    Services/slangphrase.h \
    Services/slanguage.h \
    Services/slangword.h \
    Services/stextbook.h \
    Services/sunitphrase.h \
    Services/sunitword.h \
    Services/susersetting.h \
    Services/susmapping.h \
    Services/svoice.h \
    Shared/commonapi.h \
    UI/mainwindow.h \
    UI/settingsdialog.h \
    UI/wordsunitwindow.h \
    ViewModels/vmsettings.h \
    Services/swordfami.h \
    ViewModels/vmwordsunit.h \
    UI/wordsunitwordsmodel.h

FORMS += \
    Old/selectunitsdialog.ui \
    Old/wordsonlinedialog.ui \
    UI/mainwindow.ui \
    UI/settingsdialog.ui \
    UI/wordsunitwindow.ui

