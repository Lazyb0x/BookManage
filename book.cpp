#include "Book.h"
#include <QString>

Book & Book::operator =(const Book & a)
{
    number=a.number;
    name=a.name;
    publisher=a.publisher;
    author=a.author;
    stock=a.stock;
    price=a.price;
    ID=a.ID;
    date=a.date;
    return *this;
}

Book::Book()
{
    number = stock = price = 0;
    name = publisher = author = "";
}


bool Book::isAvailable()
{
    if (ID.size()<stock)
        return true;
    else return false;
}

bool Book::SetBorrow(QString ID,QString date)
{
    if (isAvailable())
    {
        this->ID.push_back(ID);
        this->date.push_back(date);
        return true;
    }
    else return false;
}

bool Book::Returned(QString ID)
{
    int n = -1;
    for (int i=0;i<this->ID.size();i++)
    {
        if (this->ID[i] == ID)
        {
            this->ID.erase(this->ID.begin()+i);
            date.erase(date.begin()+i);
            n = i;
        }
    }
    if (n == -1) return false;
    else return true;
}

void Book::InputBook(int number, QString name, QString publisher, QString author, int stock, double price)
{
    this->number=number;
    this->name=name;
    this->publisher=publisher;
    this->author=author;
    this->stock=stock;
    this->price=price;
}
