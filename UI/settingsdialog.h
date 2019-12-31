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

    void on_cboLang_activated(int index);

    void on_cboMacVoice_activated(int index);

    void on_cboDictItem_activated(int index);

    void on_cboDictNote_activated(int index);

    void on_cboDictTranslation_activated(int index);

    void on_cboTextbook_activated(int index);

    void on_cboUnitFrom_activated(int index);

    void on_cboPartFrom_activated(int index);

    void on_cboToType_activated(int index);

    void on_cboUnitTo_activated(int index);

    void on_cboPartTo_activated(int index);

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

private:

    virtual void onGetData() override;
    virtual void onUpdateLang() override;
    virtual void onUpdateTextbook() override;
    virtual void onUpdateUnitFrom() override;
    virtual void onUpdatePartFrom() override;
    virtual void onUpdateUnitTo() override;
    virtual void onUpdatePartTo() override;

    Ui::SettingsDialog *ui;
    VMSettings& vm;
};

#endif // SETTINGSDIALOG_H
