# 图书管理系统(B树)

使用`Qt5.7`制作的基于B-树的图书管理系统。数据结构课程设计项目。

### 图书管理

能够动态地添加、删除、修改图书信息，添加借阅者等。

![图书管理主界面](https://github.com/Lazyb0x/Archives/raw/master/Release/BookManage/BM.mainwindow.png)

### B树显示

使用B树作为数据存储结构，默认阶数为4，即*2-4树*。阶数可在`BTree.h`中修改。B树的元素添加删除操作，节点的合并分裂，图形化显示是整个项目中最难的部分，花了我80%的时间。

![B树显示界面](https://github.com/Lazyb0x/Archives/raw/master/Release/BookManage/BM.B-Tree.png)

其中`BTree.h`文件完全使用C++的STL库编写，可以单独取出在非Qt环境下使用。

函数的结构和绘图很多参考自[雅乐网](www.yalewoo.com)。Github:[地址](https://github.com/yalewoo/cpp-data-structure)。

### 下载

这里有编译完成的文件:
* Windows : [BookManage.exe](https://github.com/Lazyb0x/Archives/raw/master/Release/BookManage/BookManage.exe)


