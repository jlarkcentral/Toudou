#include <QtGui/QApplication>

#include "firstwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    w.show();

    // test xml
    Tache * t = new Tache("fdsfd");
    t->tacheToXml();
    

    return a.exec();
}
