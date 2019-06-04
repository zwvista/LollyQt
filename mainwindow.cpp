#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wordsonlinedialog.h"
#include "selectunitsdialog.h"


#include "Models/mautocorrect.h"
#include "Models/munitword.h"
#include "restapi.h"


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
//    RestApi<MAutoCorrects> api("https://zwvista.tk/lolly/api.php/records/");
//    api.getObject("AUTOCORRECT?filter=LANGID,eq,3").subscribe([](const MAutoCorrects& o){
//        int i = 0;
//    });
    RestApi<MUnitWords> api("https://zwvista.tk/lolly/api.php/records/");
    api.getObject("VUNITWORDS?filter=TEXTBOOKID,eq,703&filter=UNITPART,bt,11,11&order=UNITPART&order=SEQNUM").subscribe([](const MUnitWords& o){
        int i = 0;
    });
}

void MainWindow::on_actionSelectUnits_triggered()
{
    SelectUnitsDialog dlg;
    dlg.exec();
}
