#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

namespace Ui {
class addDialog;
}

class addDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addDialog(QWidget *parent = 0);

    int number;
    QString name;
    QString publisher;
    QString author;
    int stock;
    double price;

    bool isAccepted;

    ~addDialog();

private slots:
    void on_cancelButton_clicked();

    void on_okButton_clicked();

private:
    Ui::addDialog *ui;
};

#endif // ADDDIALOG_H
