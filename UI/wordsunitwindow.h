#ifndef WORDSUNITWINDOW_H
#define WORDSUNITWINDOW_H

#include <QMainWindow>

namespace Ui {
class WordsUnitWindow;
}

class WordsUnitWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WordsUnitWindow(QWidget *parent = nullptr);
    ~WordsUnitWindow();

private:
    Ui::WordsUnitWindow *ui;
};

#endif // WORDSUNITWINDOW_H
