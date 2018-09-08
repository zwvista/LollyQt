#ifndef WORDSONLINEDIALOG_H
#define WORDSONLINEDIALOG_H

#include <QDialog>
#include "lollydb.h"
#include "wordsonlineviewmodel.h"

namespace Ui {
class WordsOnlineDialog;
}

class WordsOnlineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WordsOnlineDialog(QWidget *parent = 0);
    ~WordsOnlineDialog();

private slots:
    void on_cboLang_currentIndexChanged(int index);

    void on_btnGo_clicked();

private:
    Ui::WordsOnlineDialog *ui;
    WordsOnlineViewModel vm;
};

#endif // WORDSONLINEDIALOG_H
