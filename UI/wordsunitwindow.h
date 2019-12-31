#ifndef WORDSUNITWINDOW_H
#define WORDSUNITWINDOW_H

#include <QMainWindow>
#include "ViewModels/vmwordsunit.h"
#include "wordsunitwordsmodel.h"

namespace Ui {
class WordsUnitWindow;
}

class WordsUnitWindow : public QMainWindow, public LollyInterface
{
    Q_OBJECT

public:
    explicit WordsUnitWindow(QWidget *parent = nullptr);
    ~WordsUnitWindow() override;
    void settingsChanged() override;

    unique_ptr<VMWordsUnit> vmWordsUnit;

private:
    Ui::WordsUnitWindow *ui;

    WordsUnitWordsModel tmWords;
};

#endif // WORDSUNITWINDOW_H
