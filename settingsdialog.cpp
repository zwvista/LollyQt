#include <range/v3/all.hpp>
using namespace ranges;
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    for (auto& s : vm.toTypes)
        ui->cboToType->addItem(QString::fromStdString(s));
    vm.delegate = this;
    vm.getData().subscribe();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::onGetData()
{
    for (auto& o : vm.languages)
        ui->cboLang->addItem(QString::fromStdString(o.LANGNAME));
    ui->cboLang->setCurrentIndex(vm.selectedLangIndex);
}

void SettingsDialog::onUpdateLang()
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
    onUpdateTextbook();
}

void SettingsDialog::onUpdateTextbook()
{
    ui->cboUnitFrom->clear();
    ui->cboUnitTo->clear();
    for (auto& o : vm.getUnits()) {
        ui->cboUnitFrom->addItem(QString::fromStdString(o.label));
        ui->cboUnitTo->addItem(QString::fromStdString(o.label));
    }
    int index = ranges::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.getUSUNITFROM();
    }) - vm.getUnits().begin();
    ui->cboUnitFrom->setCurrentIndex(index);
    index = ranges::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.getUSUNITTO();
    }) - vm.getUnits().begin();
    ui->cboUnitTo->setCurrentIndex(index);
    ui->cboPartFrom->clear();
    ui->cboPartTo->clear();
    for (auto& o : vm.getParts()) {
        ui->cboPartFrom->addItem(QString::fromStdString(o.label));
        ui->cboPartTo->addItem(QString::fromStdString(o.label));
    }
    index = ranges::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.getUSPARTFROM();
    }) - vm.getParts().begin();
    ui->cboPartFrom->setCurrentIndex(index);
    index = ranges::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.getUSPARTTO();
    }) - vm.getParts().begin();
    ui->cboPartTo->setCurrentIndex(index);
    ui->lblUnitsInAllFrom->setText(QString::fromStdString(vm.getUnitsInAll()));
    ui->lblUnitsInAllTo->setText(QString::fromStdString(vm.getUnitsInAll()));
}
