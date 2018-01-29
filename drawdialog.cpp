#include "drawdialog.h"
#include "ui_drawdialog.h"
#include <QPainter>
#include <queue>
#include <QString>
#include <string>

drawDialog::drawDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::drawDialog)
{
    ui->setupUi(this);
    BT = NULL;
}


void drawDialog::paintEvent(QPaintEvent *)
{
    if (!BT) close();
    QPainter painter(this);
    queue<BTNodeP(Book)> q;
    BTNodeP(Book) x = BT->root;
    q.push(x);
    while(!q.empty())           //第一次画线
    {
        x = q.front();
        q.pop();
        if (x)
        {
            if (x && x->parent)
                painter.drawLine(70*x->x,100*x->y,70*x->parent->x,100*x->parent->y);

            for (int i=0;i<x->child.size();i++)
            {
                q.push(x->child[i]);
            }
        }
    }

    x = BT->root;
    q.push(x);
    while(!q.empty())           //第二次画方框,文字
    {
        x = q.front();
        q.pop();
        if (x)
        {
            QString s;
            string stds; x->printBTNode(stds);
            s = QString::fromStdString(stds);
            painter.setBrush(Qt::yellow);
            painter.drawRect(70*x->x-34,100*x->y-16,68,20);
            painter.drawText(70*x->x-29,100*x->y,s);

            for (int i=0;i<x->child.size();i++)
            {
                q.push(x->child[i]);
            }
        }
    }
}

drawDialog::~drawDialog()
{
    delete ui;
}
