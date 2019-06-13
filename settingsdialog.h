#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ViewModels/vmsettings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

private slots:

    void on_cboLang_currentIndexChanged(int index);

    void on_cboTextbook_currentIndexChanged(int index);

private:
    Ui::SettingsDialog *ui;
    VMSettings vm;
};

#endif // SETTINGSDIALOG_H
