#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Old/lollydb.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionWordsOnline_triggered();

    void on_actionSelectUnits_triggered();

    void on_actionSettings_triggered();

    void on_actionWords_in_Unit_triggered();

private:
    Ui::MainWindow *ui;
    LollyDB db;
};

#endif // MAINWINDOW_H
