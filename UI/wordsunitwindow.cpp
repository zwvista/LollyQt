#include "wordsunitwindow.h"
#include "ui_wordsunitwindow.h"

WordsUnitWindow::WordsUnitWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WordsUnitWindow)
{
    ui->setupUi(this);
    ui->tblWords->setModel(&tmWords);
    settingsChanged();
}

WordsUnitWindow::~WordsUnitWindow()
{
    delete ui;
}

void WordsUnitWindow::settingsChanged()
{
    vmWordsUnit = make_unique<VMWordsUnit>(vmSettings, true);
    vmWordsUnit->reload().subscribe([&](int){
        tmWords.vmWordsUnit = vmWordsUnit.get();
        tmWords.layoutChanged();
    });
}
