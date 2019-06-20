#include "wordsunitwindow.h"
#include "ui_wordsunitwindow.h"

WordsUnitWindow::WordsUnitWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WordsUnitWindow)
{
    ui->setupUi(this);
}

WordsUnitWindow::~WordsUnitWindow()
{
    delete ui;
}
