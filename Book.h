#ifndef BOOK_H
#define BOOK_H
#include <QString>
#include <vector>
using namespace std;

class Book
{
public:
    int number;				//书号
    QString name;			//书名
    QString publisher;		//出版社
    QString author;			//作者
    int stock;				//库存
    double price;			//价格

    Book();
    void Output();
    void OutputDetails();

    vector<QString> ID;				//借阅者学号
    vector<QString> date;			//应还日期

    void InputBook(int number,QString name,QString publisher,QString author,int stock,double price);
    bool SetBorrow(QString ID,QString date);
    bool isAvailable();
    bool Returned(QString ID);

    Book & operator=(const Book &a);    //重载"="操作
};

#endif // BOOK_H
