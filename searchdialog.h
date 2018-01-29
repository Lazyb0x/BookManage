#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include "BTree.h"
#include "Book.h"
namespace Ui {
class searchDialog;
}

class searchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit searchDialog(QWidget *parent = 0);
    bool isFound;
    BTree<Book> *BT;
    Book *b;
    void gerTree(BTree<Book> *p);
    ~searchDialog();

private slots:
    void on_searchButton_clicked();

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::searchDialog *ui;
};

#endif // SEARCHDIALOG_H
