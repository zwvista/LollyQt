#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wordsonlinedialog.h"
#include "selectunitsdialog.h"
#include "settingsdialog.h"

#include "Models/mautocorrect.h"
#include "Models/munitword.h"
#include "Helpers/restapi.h"
#include "Models/mlanguage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionWordsOnline_triggered()
{
//    WordsOnlineDialog dlg;
//    dlg.exec();
    SettingsDialog dlg;
    dlg.exec();
//    RestApi<MLanguages> apis;
//    auto url = "LANGUAGES?filter=ID,neq,0";
//    apis.getObject(url).map([](const MLanguages& o){
//        return o.records;
//    }).subscribe([](const auto& o){
//        int i = 0;
//    });
}

void MainWindow::on_actionSelectUnits_triggered()
{
    SelectUnitsDialog dlg;
    dlg.exec();
}
