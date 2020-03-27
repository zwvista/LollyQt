#include <range/v3/all.hpp>
using namespace ranges;
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    vm(vmSettings)
{
    ui->setupUi(this);

    for (auto& s : vm.toTypes)
        ui->cboToType->addItem(QString::fromStdString_t(s));

    vm.delegate = this;
    vm.getData().subscribe();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
    vm.delegate = nullptr;
}

void SettingsDialog::onGetData()
{
    for (auto& o : vm.languages)
        ui->cboLang->addItem(QString::fromStdString_t(o.LANGNAME));
    ui->cboLang->setCurrentIndex(vm.selectedLangIndex);
}

void SettingsDialog::onUpdateLang()
{
    ui->cboMacVoice->clear();
    for (auto& o : vm.macVoices)
        ui->cboMacVoice->addItem(QString::fromStdString_t(o.VOICENAME));
    ui->cboMacVoice->setCurrentIndex(vm.selectedMacVoiceIndex);

    ui->cboDictItem->clear();
    for (auto& o : vm.dictItems)
        ui->cboDictItem->addItem(QString::fromStdString_t(o.DICTNAME));
    ui->cboDictItem->setCurrentIndex(vm.selectedDictItemIndex);

    ui->cboDictNote->clear();
    for (auto& o : vm.dictsNote)
        ui->cboDictNote->addItem(QString::fromStdString_t(o.DICTNAME));
    ui->cboDictNote->setCurrentIndex(vm.selectedDictNoteIndex);

    ui->cboDictTranslation->clear();
    for (auto& o : vm.dictsTranslation)
        ui->cboDictTranslation->addItem(QString::fromStdString_t(o.DICTNAME));
    ui->cboDictTranslation->setCurrentIndex(vm.selectedDictTranslationIndex);

    ui->cboTextbook->clear();
    for (auto& o : vm.textbooks)
        ui->cboTextbook->addItem(QString::fromStdString_t(o.TEXTBOOKNAME));
    ui->cboTextbook->setCurrentIndex(vm.selectedTextbookIndex);

    onUpdateTextbook();
}

void SettingsDialog::onUpdateTextbook()
{
    ui->cboUnitFrom->clear();
    ui->cboUnitTo->clear();
    for (auto& o : vm.getUnits()) {
        ui->cboUnitFrom->addItem(QString::fromStdString_t(o.label));
        ui->cboUnitTo->addItem(QString::fromStdString_t(o.label));
    }
    onUpdateUnitFrom();
    onUpdatePartFrom();

    ui->cboPartFrom->clear();
    ui->cboPartTo->clear();
    for (auto& o : vm.getParts()) {
        ui->cboPartFrom->addItem(QString::fromStdString_t(o.label));
        ui->cboPartTo->addItem(QString::fromStdString_t(o.label));
    }
    onUpdateUnitTo();
    onUpdatePartTo();

    ui->lblUnitsInAllFrom->setText(QString::fromStdString_t(vm.getUnitsInAll()));
    ui->lblUnitsInAllTo->setText(QString::fromStdString_t(vm.getUnitsInAll()));

    ui->cboToType->setCurrentIndex(static_cast<int>(vm.toType));
    on_cboToType_activated(static_cast<int>(vm.toType));
}

void SettingsDialog::onUpdateUnitFrom()
{
    int index = ranges::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.USUNITFROM();
    }) - vm.getUnits().begin();
    ui->cboUnitFrom->setCurrentIndex(index);
}

void SettingsDialog::onUpdatePartFrom()
{
    int index = ranges::find_if(vm.getUnits(), [&](const MSelectItem& o){
        return o.value == vm.USUNITTO();
    }) - vm.getUnits().begin();
    ui->cboUnitTo->setCurrentIndex(index);
}

void SettingsDialog::onUpdateUnitTo()
{
    int index = ranges::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.USPARTFROM();
    }) - vm.getParts().begin();
    ui->cboPartFrom->setCurrentIndex(index);
}

void SettingsDialog::onUpdatePartTo()
{
    int index = ranges::find_if(vm.getParts(), [&](const MSelectItem& o){
        return o.value == vm.USPARTTO();
    }) - vm.getParts().begin();
    ui->cboPartTo->setCurrentIndex(index);
}

void SettingsDialog::on_cboLang_activated(int index)
{
    vm.setSelectedLang(index).subscribe();
}

void SettingsDialog::on_cboMacVoice_activated(int index)
{
    vm.setSelectedMacVoice(index);
    vm.updateMacVoice().subscribe();
}

void SettingsDialog::on_cboDictItem_activated(int index)
{
    vm.setSelectedDictItem(index);
    vm.updateDictItem().subscribe();
}

void SettingsDialog::on_cboDictNote_activated(int index)
{
    vm.setSelectedDictNote(index);
    vm.updateDictItem().subscribe();
}

void SettingsDialog::on_cboDictTranslation_activated(int index)
{
    vm.setSelectedDictTranslation(index);
    vm.updateDictTranslation().subscribe();
}

void SettingsDialog::on_cboTextbook_activated(int index)
{
    vm.setSelectedTextbook(index);
    vm.updateTextbook().subscribe();
}

void SettingsDialog::on_cboUnitFrom_activated(int index)
{
    vm.USUNITFROM(vm.getUnits()[index].value);
    vm.updateUnitFrom().subscribe();
}

void SettingsDialog::on_cboPartFrom_activated(int index)
{
    vm.USPARTFROM(vm.getParts()[index].value);
    vm.updatePartFrom().subscribe();
}

void SettingsDialog::on_cboToType_activated(int index)
{
    vm.toType = static_cast<UnitPartToType>(index);
    bool b = vm.toType == UnitPartToType::TO;
    ui->cboUnitTo->setEnabled(b);
    ui->cboPartTo->setEnabled(b && !vm.isSinglePart());
    ui->btnPrevious->setEnabled(!b);
    ui->btnNext->setEnabled(!b);
    bool b2 = vm.toType != UnitPartToType::UNIT;
    auto t = !b2 ? QString("Unit") : QString("Part");
    ui->btnPrevious->setText("Previous " + t);
    ui->btnNext->setText("Next " + t);
    ui->cboPartFrom->setEnabled(b2 && !vm.isSinglePart());
    vm.updateToType().subscribe();
}

void SettingsDialog::on_cboUnitTo_activated(int index)
{
    vm.USUNITTO(vm.getUnits()[index].value);
    vm.updateUnitTo().subscribe();
}

void SettingsDialog::on_cboPartTo_activated(int index)
{
    vm.USPARTFROM(vm.getParts()[index].value);
    vm.updatePartTo().subscribe();
}

void SettingsDialog::on_btnPrevious_clicked()
{
    vm.previousUnitPart().subscribe();
}

void SettingsDialog::on_btnNext_clicked()
{
    vm.nextUnitPart().subscribe();
}
