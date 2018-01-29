#include "borrowinfodialog.h"
#include "ui_borrowinfodialog.h"
#include "QStandardItemModel"
#include <QString>
#include <QInputDialog>

borrowInfoDialog::borrowInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowInfoDialog)
{
    ui->setupUi(this);

    B = NULL;

    model = new QStandardItemModel;
    model->setColumnCount(2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromUtf8("学号"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("归还日期"));
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->setColumnWidth(0,40);
    displayTable();
}

borrowInfoDialog::~borrowInfoDialog()
{
    delete ui;
}

void borrowInfoDialog::displayTable()
{
    if (!B) return;
    model->removeRows(0,model->rowCount());
    for (int i=0;i<B->ID.size();i++)
    {
        model->setItem(i,0,new QStandardItem(B->ID[i]));
        model->setItem(i,1,new QStandardItem(B->date[i]));
    }
    QString info = "《 "+B->name+" 》的借阅者信息";
    ui->groupBox->setTitle(info);
}

void borrowInfoDialog::on_addButton_clicked()
{
    bool ok1,ok2;
    QString ID = QInputDialog::getText(this,tr("添加"),tr("输入借阅者ID："),QLineEdit::Normal,NULL,&ok1);
    QString date = QInputDialog::getText(this,tr("添加"),tr("归还日期："),QLineEdit::Normal,NULL,&ok2);
    if (ok1&&ok2&&ID!=""&&date!="")
    {
        B->SetBorrow(ID,date);
        displayTable();
    }

}

void borrowInfoDialog::on_delButton_clicked()
{
    bool ok;
    QString ID = QInputDialog::getText(this,tr("删除"),tr("输入借阅者ID："),QLineEdit::Normal,NULL,&ok);
    if (ok)
    {
        B->Returned(ID);
        displayTable();
    }
}

void borrowInfoDialog::on_exitButton_clicked()
{
    close();
}
