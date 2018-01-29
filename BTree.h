#ifndef BTREE_H
#define BTREE_H
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#define BTNodeP(T) BTNode<T>*
#define output cout
#define M 4                             //阶数,M>=3
using namespace std;

template <class T>
class BTNode
{
    public:

        BTNode();
        BTNodeP(T) parent;              //双亲节点
        vector<int> key;                //元素
        vector<T> record;				//记录类型,需要定义"<<"及"="操作
        vector<BTNodeP(T)> child;       //孩子

        int x;							//绘图x轴坐标
        int y;							//绘图y轴坐标
        void printBTNode();             //打印节点元素
        void printBTNode(string &s);
        void printChild();              //打印节点的孩子树
        void printParent();             //打印双亲
        void printRecord();             //打印节点的孩子的记录
        int search(int e);              //查找元素，返回所在位置

    private:

        void printChild(string s);
        string Int_to_String(int n);
};

template <class T>
class BTree
{
    public:

        int size;                               //节点数量
        BTNodeP(T) root;                        //根节点
        BTNodeP(T) currrent;                    //缓存节点，用于添加删除操作
        int px;                                 //绘图x轴坐标计数器

        BTNodeP(T) search(int e);
        bool insert(int e);
        bool insertRecord(int e,T & record);
        bool remove(int e);
        void display();
        void calcuPaint();						//计算绘图坐标

        BTree();

    private:

        void solveOverFlow(BTNodeP(T) p);       //分裂节点
        void solveUnderFlow(BTNodeP(T) P);      //合并节点
        void calcuPaint(BTNodeP(T) p,int py);   //计算绘图坐标
};

template <class T>
string BTNode<T>::Int_to_String(int n)
{
    ostringstream stream;
    stream<<n;
    return stream.str();
}

template <class T>
BTNode<T>::BTNode()
{
    parent = NULL;
}

template <class T>
void BTNode<T>::printBTNode(string &s)
{
    s = "";
    if (this == NULL)
    {
        return;
    }
    s += "[";
    for (int i=0;i<key.size();i++)
    {
        s+=Int_to_String(key[i]);
        if (i!=key.size()-1) s+=" ";
    }

    s += "]";
}

template <class T>
void BTNode<T>::printBTNode()
{
    string s;
    printBTNode(s);
    output<<s;
}

template <class T>
void BTNode<T>::printRecord()
{
    for (int i=0;i<record.size();i++)
    {
        cout<<record[i]<<'\n';
    }
    for (int i=0;i<child.size();i++)
    {
        child[i]->printRecord();
    }
}

template <class T>
void BTNode<T>::printParent()
{
    printBTNode();
    output<<"=";parent->printBTNode();
    output<<'\n';
    for (int i=0;i<child.size();i++)
    {
        child[i]->printParent();
    }
}

template <class T>
void BTNode<T>::printChild()
{
    string s = "";
    printChild(s);
}

template <class T>
void BTNode<T>::printChild(string s)
{
    output<<s;
    s+="    ";
    printBTNode();
    output<<'\n';
    for (int i=0;i<child.size();i++)
    {
        child[i]->printChild(s);
    }
}

template <class T>
int BTNode<T>::search(int e)
{
    int n = -1;
    for (int i=0;i<key.size();i++)
    {
        if (key[i]<=e) n = i;
        else break;
    }
    return n;
}

template <class T>
BTNodeP(T) BTree<T>::search(int e)
{
    BTNodeP(T) p = root;
    currrent = NULL;
    while(p)
    {
        int n = p->search(e);
        if (n!=-1)
            if (p->key[n]==e)
            {
                //output<<"###找到,节点内元素为:";
                //p->printBTNode();
                //output<<'\n';
                currrent = p;
                return p;					//找到并返回指针
            }

        if (p->child.size())				//是否已到叶子节点
        {
            p = p->child[n+1];
        }
        else
        {
            currrent = p;					//未找到，标记位置
            //output<<"###未找到,位置:";
            //p->printBTNode();
            //output<<'\n';
            break;
        }
    }
    return NULL;
}

template <class T>
bool BTree<T>::insert(int e)
{
    T record;									//空记录，不做任何用
    return insertRecord(e,record);
}

template <class T>
bool BTree<T>::insertRecord(int e,T & record)
{
    if (root == NULL)
    {
        root = new BTNode<T>;
    }
    if (search(e)) return false;
    BTNodeP(T) p = currrent;
    int n = p->search(e);
    p->key.insert(p->key.begin()+n+1,e);
    p->record.insert(p->record.begin()+n+1,record);
    if (p->key.size()>=M) solveOverFlow(p);
    calcuPaint();
    return true;
}

template <class T>
bool BTree<T>::remove(int e)
{
    if (!search(e)) return false;
    BTNodeP(T) p = currrent;
    int n = p->search(e);

    if (p->child.size())						//不是叶子节点，用叶子节点换
    {
        BTNodeP(T) q = p->child[n+1];				//向右，然后左转走到尽头
        while(q->child.size())
        {
            q = q->child[0];
        }
        p->key[n]=q->key[0];
        p->record[n]=q->record[0];
        n = 0;
        p = q;
    }
    p->key.erase(p->key.begin()+n);
    p->record.erase(p->record.begin()+n);
    if (p != root && p->key.size()<((M+1)/2-1))
    {
        solveUnderFlow(p);
    }
    if (p == root && p->key.size() == 0 && p->child.size() == 0) root = NULL;
    calcuPaint();
    return true;
}

template <class T>
void BTree<T>::solveOverFlow(BTNodeP(T) p)
{
    int n = (M+1)/2;
    int upkey = p->key[n-1];
    T uprecord = p->record[n-1];
    BTNodeP(T) p2 = new BTNode<T>;				//分裂出的新节点
    p2->parent = p->parent;
    for (int i=0;i<n-1;i++)
    {
        p2->key.push_back(p->key[i]);
        p2->record.push_back(p->record[i]);
    }
    for (int i=0;i<n;i++)
    {
        p->key.erase(p->key.begin());
        p->record.erase(p->record.begin());
    }
    if (p->child.size())								//是否叶子节点
    {
        for (int i=0;i<n;i++)
            {
                p->child[0]->parent = p2;				//孩子交给新的双亲
                p2->child.push_back(p->child[0]);
                p->child.erase(p->child.begin());
            }
    }

    BTNodeP(T) pa = p->parent;

    if (!pa)							//p是根节点
    {
        pa = new BTNode<T>;
        p2->parent = p->parent = pa;		//重新设置分裂出去节点的双亲
        pa->key.push_back(upkey);
        pa->record.push_back(uprecord);
        pa->child.push_back(p2);
        pa->child.push_back(p);
        root = pa;									//新的根节点
    }
    else
    {
        int x = pa->search(upkey);
        pa->key.insert(pa->key.begin()+x+1,upkey);
        pa->record.insert(pa->record.begin()+x+1,uprecord);
        pa->child.insert(pa->child.begin()+x+1,p2);
    }

    if (pa->key.size()>=M) solveOverFlow(pa);		//往上继续查找
}

template <class T>
void BTree<T>::solveUnderFlow(BTNodeP(T) p)
{
    if (p == root)
    {
        if (p->key.size() == 0 && p->child.size() == 0) root = NULL;		//真·根节点空,不会出现,但为了保险
        if (p->key.size() == 0 && p->child.size() > 0)
        {
            root = p->child[0];										//改变根节点，这时只可能有1个孩子
            p->child[0]->parent = NULL;
        }
        return;
    }

    int n;
    for (int i=0;i<p->parent->child.size();i++)						//找出p在双亲中的位置
    {
        if (p == p->parent->child[i]) n = i;
    }

    if (n != 0)														//p有左兄弟
    {
        BTNodeP(T) leftBro = p->parent->child[n-1];
        if (leftBro->key.size()>(((M+1)/2)-1))
        {
            p->key.insert(p->key.begin(),p->parent->key[n-1]);
            p->record.insert(p->record.begin(),p->parent->record[n-1]);
            p->parent->key[n-1] = leftBro->key[leftBro->key.size()-1];
            p->parent->record[n-1] = leftBro->record[leftBro->record.size()-1];
            //leftBro->key.erase(leftBro->key.end());
            leftBro->key.erase(leftBro->key.begin()+leftBro->key.size()-1);
            //leftBro->record.erase(leftBro->record.end());
            leftBro->record.erase(leftBro->record.begin()+leftBro->record.size()-1);
            if (p->child.size())
            {
                leftBro->child[leftBro->child.size()-1]->parent = p;
                p->child.insert(p->child.begin(),leftBro->child[leftBro->child.size()-1]);
                //leftBro->child.erase(leftBro->child.end());
                leftBro->child.erase(leftBro->child.begin()+leftBro->child.size()-1);
            }
            return;
        }
        else														//合并节点操作
        {
            leftBro->key.push_back(p->parent->key[n-1]);
            leftBro->record.push_back(p->parent->record[n-1]);
            for (int i=0;i<p->key.size();i++)
            {
                leftBro->key.push_back(p->key[i]);
                leftBro->record.push_back(p->record[i]);
            }
            for (int i=0;i<p->child.size();i++)
            {
                p->child[i]->parent = leftBro;						//孩子的双亲是左兄弟
                leftBro->child.push_back(p->child[i]);
            }
            p->parent->key.erase(p->parent->key.begin()+n-1);
            p->parent->record.erase(p->parent->record.begin()+n-1);
            p->parent->child.erase(p->parent->child.begin()+n);

            if (p->parent->key.size()<((M+1)/2-1)) solveUnderFlow(p->parent);
            return;
        }
    }
    if (n!=p->parent->child.size()-1)								//p有右兄弟
    {
        BTNodeP(T) rightBro = p->parent->child[n+1];
        if (rightBro->key.size()>(((M+1)/2)-1))
        {
            p->key.push_back(p->parent->key[n]);
            p->record.push_back(p->parent->record[n]);
            p->parent->key[n] = rightBro->key[0];
            p->parent->record[n] = rightBro->record[0];
            rightBro->key.erase(rightBro->key.begin());
            rightBro->record.erase(rightBro->record.begin());
            if (p->child.size())
            {
                rightBro->child[0]->parent = p;
                p->child.push_back(rightBro->child[0]);
                rightBro->child.erase(rightBro->child.begin());
            }
            return;
        }
        else
        {
            rightBro->key.insert(rightBro->key.begin(),p->parent->key[n]);
            rightBro->record.insert(rightBro->record.begin(),p->parent->record[n]);
            for (int i=p->key.size()-1;i>=0;i--)
            {
                rightBro->key.insert(rightBro->key.begin(),p->key[i]);
                rightBro->record.insert(rightBro->record.begin(),p->record[i]);
            }
            for (int i=p->child.size()-1;i>=0;i--)
            {
                p->child[i]->parent = rightBro;
                rightBro->child.insert(rightBro->child.begin(),p->child[i]);
            }
            p->parent->key.erase(p->parent->key.begin()+n);
            p->parent->record.erase(p->parent->record.begin()+n);
            p->parent->child.erase(p->parent->child.begin()+n);

            if (p->parent->key.size()<((M+1)/2-1)) solveUnderFlow(p->parent);
            return;
        }
    }
}

template <class T>
void BTree<T>::display()
{
    if (root) root->printChild();
}

template <class T>
void BTree<T>::calcuPaint()
{
    size = 0;
    px = 1;
    calcuPaint(root,1);
}

template <class T>
void BTree<T>::calcuPaint(BTNodeP(T) p,int py)
{
    if (p == NULL) return;
    size +=p->key.size();
    p->y = py++;									//对于y轴用前序遍历
    int n = (p->child.size()+1)/2;
    for (int i=0;i<n;i++)
    {
        calcuPaint(p->child[i],py);
    }
    p->x = px++;									//对于x轴用类似的中序遍历
    for (int i=n;i<p->child.size();i++)
    {
        calcuPaint(p->child[i],py);
    }
}

template <class T>
BTree<T>::BTree()
{
    size = 0;
    root = NULL;
    currrent = NULL;
}

#endif // BTREE_H
