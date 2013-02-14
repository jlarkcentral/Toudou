#include <QtGui/QApplication>

#include "firstwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    FirstWindow w;
    w.show();

    // test xml
    Tache * t = new Tache("tester la sauvegarde xml");
    Tache * st1 = new Tache("faire des trucs");
    Tache * st2 = new Tache("blibli");
    Tache * st3 = new Tache("blabla");

    t->addSousTache(*st1);
    t->addSousTache(*st2);
    t->addSousTache(*st3);

    Tache * sst1 = new Tache("truc 1");
    Tache * sst2 = new Tache("truc 2");

    st1->addSousTache(*sst1);
    st1->addSousTache(*sst2);

    t->createXml();

    t->display();

    cout << "############" << endl;

    st1->display();

    return a.exec();
}
