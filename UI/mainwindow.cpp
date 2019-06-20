#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../Old/wordsonlinedialog.h"
#include "../Old/selectunitsdialog.h"
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
}

void MainWindow::on_actionSelectUnits_triggered()
{
    SelectUnitsDialog dlg;
    dlg.exec();
}
