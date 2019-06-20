#ifndef SELECTUNITSDIALOG_H
#define SELECTUNITSDIALOG_H

#include <QDialog>
#include "selectunitsviewmodel.h"

namespace Ui {
class SelectUnitsDialog;
}

class SelectUnitsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectUnitsDialog(QWidget *parent = 0);
    ~SelectUnitsDialog();

private slots:
    void on_cboLang_activated(int index);

    void on_cboTextbook_activated(int index);

private:
    Ui::SelectUnitsDialog *ui;
    SelectUnitsViewModel vm;
};

#endif // SELECTUNITSDIALOG_H
