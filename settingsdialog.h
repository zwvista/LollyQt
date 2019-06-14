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

    void on_cboLang_currentIndexChanged(int index);

    void on_cboVoice_currentIndexChanged(int index);

    void on_cboDictItem_currentIndexChanged(int index);

    void on_cboDictNote_currentIndexChanged(int index);

    void on_cboDictTranslation_currentIndexChanged(int index);

    void on_cboTextbook_currentIndexChanged(int index);

private:

    virtual void onGetData() override;
    virtual void onUpdateLang() override;
    virtual void onUpdateTextbook() override;

    Ui::SettingsDialog *ui;
    VMSettings vm;
};

#endif // SETTINGSDIALOG_H
