#ifndef BORROWINFODIALOG_H
#define BORROWINFODIALOG_H

#include <QDialog>
#include "QStandardItemModel"
#include "Book.h"

namespace Ui {
class borrowInfoDialog;
}

class borrowInfoDialog : public QDialog
{
    Q_OBJECT

public:

    QStandardItemModel *model;
    Book  *B;
    void displayTable();
    void getBook(Book *p){B = p;}

    explicit borrowInfoDialog(QWidget *parent = 0);
    ~borrowInfoDialog();

private slots:
    void on_addButton_clicked();

    void on_delButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::borrowInfoDialog *ui;
};

#endif // BORROWINFODIALOG_H
