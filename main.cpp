#include <QtGui/QApplication>
#include "mainwindow.h"
#include "firstwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    w.show();



    int i = 5; // test perso uniquement pour le commit
    
    return a.exec();
}
