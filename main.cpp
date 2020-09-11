#include "UI/mainwindow.h"
#include <QApplication>
#include <rxqt.hpp>
#include <ViewModels/vmsettings.h>

const rxqt::run_loop* pRunLoop;
const uri base_uri{_XPLATSTR("https://zwvista.tk/lolly/api.php/records/")};
VMSettings vmSettings;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    rxqt::run_loop rxqt_run_loop;
    pRunLoop = &rxqt_run_loop;
    w.show();

    return a.exec();
}
