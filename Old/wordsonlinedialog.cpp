#include "wordsonlinedialog.h"
#include "ui_wordsonlinedialog.h"

WordsOnlineDialog::WordsOnlineDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WordsOnlineDialog)
{
    ui->setupUi(this);

    vm.setQueryLang();
    ui->cboLang->setModel(vm.mdlLang);
    ui->cboLang->setModelColumn(1);
}

WordsOnlineDialog::~WordsOnlineDialog()
{
    delete ui;
}

void WordsOnlineDialog::on_cboLang_activated(int index)
{
    int langid = vm.mdlLang->record(index).value("ID").toInt();
    vm.setQueryDict(langid);
    ui->cboDict->setModel(vm.mdlDict);
    ui->cboDict->setModelColumn(0);
    ui->cboDict->setCurrentIndex(0);
}

void WordsOnlineDialog::on_btnGo_clicked()
{
    int index = ui->cboDict->currentIndex();
//    QString url = vm.mdlDict->data(vm.mdlDict->index(index, 1)).toString();
    QString url = vm.mdlDict->record(index).value("URL").toString();
    url.replace("{0}", ui->edtWord->text());
    ui->wvOnline->load(QUrl(url));
}
