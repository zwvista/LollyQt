#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <boost/range/algorithm.hpp>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    for (auto& s : vm.toTypes)
        ui->cboToType->addItem(QString::fromStdString(s));

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
    on_cboTextbook_currentIndexChanged(vm.selectedTextbookIndex);
}

void SettingsDialog::on_cboTextbook_currentIndexChanged(int)
{
    ui->cboUnitFrom->clear();
    ui->cboUnitTo->clear();
    for (auto& o : vm.getUnits()) {
        ui->cboUnitFrom->addItem(QString::fromStdString(o.label));
        ui->cboUnitTo->addItem(QString::fromStdString(o.label));
    }
    int index = boost::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.getUSUNITFROM();
    }) - vm.getUnits().begin();
    ui->cboUnitFrom->setCurrentIndex(index);
    index = boost::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.getUSUNITTO();
    }) - vm.getUnits().begin();
    ui->cboUnitTo->setCurrentIndex(index);
    ui->cboPartFrom->clear();
    ui->cboPartTo->clear();
    for (auto& o : vm.getParts()) {
        ui->cboPartFrom->addItem(QString::fromStdString(o.label));
        ui->cboPartTo->addItem(QString::fromStdString(o.label));
    }
    index = boost::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.getUSPARTFROM();
    }) - vm.getParts().begin();
    ui->cboPartFrom->setCurrentIndex(index);
    index = boost::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.getUSPARTTO();
    }) - vm.getParts().begin();
    ui->cboPartTo->setCurrentIndex(index);
    ui->lblUnitsInAllFrom->setText(QString::fromStdString(vm.getUnitsInAll()));
    ui->lblUnitsInAllTo->setText(QString::fromStdString(vm.getUnitsInAll()));
}
