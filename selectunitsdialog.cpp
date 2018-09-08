#include "selectunitsdialog.h"
#include "ui_selectunitsdialog.h"

SelectUnitsDialog::SelectUnitsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectUnitsDialog)
{
    ui->setupUi(this);

    vm.setQueryUserSettings();
    vm.setQueryLang();
    ui->cboLang->setModel(vm.mdlLang);
    ui->cboLang->setModelColumn(1);

    auto row = vm.mdlUserSettings->record(0);
    auto langid = row.value("USLANGID").toInt();
    auto indexes = vm.mdlLang->match(vm.mdlLang->index(0, 0), Qt::DisplayRole, langid);
    ui->cboLang->setCurrentIndex(indexes.first().row());
}

SelectUnitsDialog::~SelectUnitsDialog()
{
    delete ui;
}

void SelectUnitsDialog::on_cboLang_currentIndexChanged(int index)
{
    auto row = vm.mdlLang->record(index);
    auto langid = row.value("ID").toInt();
    auto textbookID = row.value("USTEXTBOOKID").toInt();
    vm.setQueryTextbook(langid);
    ui->cboTextbook->setModel(vm.mdlTextBook);
    ui->cboTextbook->setModelColumn(2);
    auto indexes = vm.mdlTextBook->match(vm.mdlTextBook->index(0, 0), Qt::DisplayRole, textbookID);
    ui->cboTextbook->setCurrentIndex(indexes.first().row());
}

void SelectUnitsDialog::on_cboTextbook_currentIndexChanged(int index)
{
    auto row = vm.mdlTextBook->record(index);
    auto units = row.value("UNITS").toInt();
    auto unitsstr = QString("(%1 in all)").arg(units);
    ui->lblUnitsInAllFrom->setText(unitsstr);
    ui->lblUnitsInAllTo->setText(unitsstr);
    auto unitfrom = row.value("USUNITFROM").toInt();
    ui->spnUnitFrom->setValue(unitfrom);
    auto unitto = row.value("USUNITTO").toInt();
    ui->spnUnitTo->setValue(unitto);
    auto parts = row.value("PARTS").toString().split(" ");
    auto partfrom = row.value("USPARTFROM").toInt();
    auto partto = row.value("USPARTTO").toInt();
    ui->cboPartFrom->clear();
    ui->cboPartFrom->addItems(parts);
    ui->cboPartFrom->setCurrentIndex(partfrom - 1);
    ui->cboPartTo->clear();
    ui->cboPartTo->addItems(parts);
    ui->cboPartTo->setCurrentIndex(partto - 1);
}

void SelectUnitsDialog::on_buttonBox_accepted()
{

}
