#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wordsonlinedialog.h"
#include "selectunitsdialog.h"

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
    WordsOnlineDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionSelectUnits_triggered()
{
    SelectUnitsDialog dlg;
    dlg.exec();
}
