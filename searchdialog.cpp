#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>

searchDialog::searchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchDialog)
{
    ui->setupUi(this);
    isFound = false;
}

void searchDialog::gerTree(BTree<Book> *p)
{
    BT = p;
}

searchDialog::~searchDialog()
{
    delete ui;
}

void searchDialog::on_searchButton_clicked()
{
    int n = ui->numEdit->text().toInt();
    if (BT->search(n))
    {
        isFound = true;
        ui->nameEdit->setText("aaea");
        int x = BT->currrent->search(n);
        b = &BT->currrent->record[x];
        ui->nameEdit->setText(b->name);
        ui->pubEdit->setText(b->publisher);
        ui->autEdit->setText(b->author);
        ui->stockEdit->setText(QString::number(b->stock,10));
        ui->priceEdit->setText(QString::number(b->price,10,2));
    }
    else
    {
        isFound = false;
        ui->nameEdit->clear();
        ui->pubEdit->clear();
        ui->autEdit->clear();
        ui->stockEdit->clear();
        ui->priceEdit->clear();
    }

}

void searchDialog::on_okButton_clicked()
{
    if (!isFound) return;
    b->name = ui->nameEdit->text();
    b->author = ui->autEdit->text();
    b->publisher = ui->pubEdit->text();
    b->stock = ui->stockEdit->text().toInt();
    b->price = ui->priceEdit->text().toDouble();
    accept();
}

void searchDialog::on_cancelButton_clicked()
{
    close();
}
