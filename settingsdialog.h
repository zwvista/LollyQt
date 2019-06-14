#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ViewModels/vmsettings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog, public VMSettingsDelegate
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:

private:

    virtual void onGetData() override;
    virtual void onUpdateLang() override;
    virtual void onUpdateTextbook() override;

    Ui::SettingsDialog *ui;
    VMSettings vm;
};

#endif // SETTINGSDIALOG_H
