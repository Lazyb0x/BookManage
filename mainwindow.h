#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QString>
#include "Book.h"
#include "BTree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    int ct;                                    //用来计数,书目总数
    QStandardItemModel *model;
    BTree<Book> BT;
    bool inputBook(int number,QString name,QString publisher,QString author,int stock,float price);
    void displayTable();

    ~MainWindow();

private slots:

    void on_addButton_clicked();

    void on_exitButton_clicked();

    void on_delButton_clicked();

    void on_borrowInfoButton_clicked();

    void on_searchButton_clicked();

    void on_BTreeButton_clicked();

private:
    Ui::MainWindow *ui;
    void displayTable(BTNodeP(Book) p);
};

#endif // MAINWINDOW_H
