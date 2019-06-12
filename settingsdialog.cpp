#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "Services/slanguage.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    vm.getData().subscribe([&](const auto&){
        for (auto& o : vm.languages)
            ui->cboLang->addItem(QString::fromStdString(o.LANGNAME));
        ui->cboLang->setCurrentIndex(vm.selectedLangIndex);
        on_cboLang_currentIndexChanged(vm.selectedLangIndex);
    });
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_cboLang_currentIndexChanged(int index)
{
    ui->cboVoice->clear();
    for (auto& o : vm.macVoices)
        ui->cboVoice->addItem(QString::fromStdString(o.VOICENAME));
    ui->cboVoice->setCurrentIndex(vm.selectedMacVoiceIndex);
    ui->cboDictItem->clear();
    for (auto& o : vm.dictItems)
        ui->cboDictItem->addItem(QString::fromStdString(o.DICTNAME));
    ui->cboDictItem->setCurrentIndex(vm.selectedDictItemIndex);
    ui->cboDictNote->clear();
    for (auto& o : vm.dictsNote)
        ui->cboDictNote->addItem(QString::fromStdString(o.DICTNAME));
    ui->cboDictNote->setCurrentIndex(vm.selectedDictNoteIndex);
    ui->cboDictTranslation->clear();
    for (auto& o : vm.dictsTranslation)
        ui->cboDictTranslation->addItem(QString::fromStdString(o.DICTNAME));
    ui->cboDictTranslation->setCurrentIndex(vm.selectedDictTranslationIndex);
    ui->cboTextbook->clear();
    for (auto& o : vm.textbooks)
        ui->cboTextbook->addItem(QString::fromStdString(o.TEXTBOOKNAME));
    ui->cboTextbook->setCurrentIndex(vm.selectedTextbookIndex);
}
