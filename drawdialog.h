#ifndef DRAWDIALOG_H
#define DRAWDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QPaintEvent>
#include <BTree.h>
#include <Book.h>

namespace Ui {
class drawDialog;
}

class drawDialog : public QDialog
{
    Q_OBJECT

public:
    BTree<Book> *BT;
    void getTree(BTree<Book> *p){BT = p;}
    void paintEvent(QPaintEvent *);

    explicit drawDialog(QWidget *parent = 0);
    ~drawDialog();
public slots:

private:
    Ui::drawDialog *ui;
};

#endif // DRAWDIALOG_H
