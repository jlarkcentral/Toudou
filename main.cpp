#include <QtGui/QApplication>
#include "mainwindow.h"
#include "firstwindow.h"




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    w.show();
<<<<<<< HEAD
=======



    int i = 5; // test perso uniquement pour le commit
>>>>>>> 02ebd9d354784eb6dcec905b5a7a3c4713b9cd42
    
    return a.exec();
}
