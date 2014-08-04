#include "mainwindow.h"
#include <QApplication>
#include <iostream>

void func(unsigned char header,double &val)
{
   // val=val/1024*360;
    std::cout<<(int)header<<" "<<val<<std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setPreProcessFunc(func);
    w.show();
    return a.exec();
}
