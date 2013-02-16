#include <QtGui/QApplication>
#include <QDesktopWidget>

#include "firstwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    // centrer la fenetre (il y a p-e un moyen plus propre)
    w.move((QApplication::desktop()->width() - w.width())/2, (QApplication::desktop()->height() - w.height())/2);
    w.show();

    return a.exec();
}
