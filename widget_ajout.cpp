
#include <QVBoxLayout>

#include "widget_ajout.h"


Widget_ajout::Widget_ajout(FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    name = new QLabel();
    //parent = new QLabel("En attente");
    date = new QLabel();
    timeleft = new QLabel("A faire");
    type = new QLabel();

    // Bouton Nouveau
    QPushButton * boutonAjout = new QPushButton("Ajouter");
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),firstW,SLOT(addTache()));
}

Widget_ajout::~Widget_ajout()
{}
