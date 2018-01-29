#include "adddialog.h"
#include "ui_adddialog.h"
#include <QString>

addDialog::addDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialog)
{
    isAccepted = false;
    ui->setupUi(this);
}

addDialog::~addDialog()
{
    delete ui;
}

void addDialog::on_cancelButton_clicked()
{
    close();
}

void addDialog::on_okButton_clicked()
{
    number = ui->numEdit->text().toInt();
    name = ui->nameEdit->text();
    publisher = ui->pubEdit->text();
    author = ui->autEdit->text();
    stock = ui->stockEdit->text().toInt();
    price = ui->priceEdit->text().toDouble();
    isAccepted = true;
    if (ui->numEdit->text() != "") accept();
}
