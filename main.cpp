#include <QtGui/QApplication>
#include "mainwindow.h"
#include "firstwindow.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    w.show();
    
    return a.exec();
}
