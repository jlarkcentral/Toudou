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
    st1->setDate("date de faire des trucs");
    Tache * st2 = new Tache("blibli");
    st2->setDate("date de blibli");
    Tache * st3 = new Tache("blabla");
    st3->setDate("date de blabla");

    t->addSousTache(*st1);
    t->addSousTache(*st2);
    t->addSousTache(*st3);

    Tache * sst1 = new Tache("truc 1");
    sst1->setDate("moment de faire truc1");
    Tache * sst2 = new Tache("truc 2");
    sst2->setDate("moment de faire truc2");

    st1->addSousTache(*sst1);
    st1->addSousTache(*sst2);

    //t->createXml();

    //t->display();
    //cout << "############" << endl;
    //st1->display();

    return a.exec();
}
