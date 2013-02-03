
#include <QVBoxLayout>
#include <QLineEdit>

#include "widget_ajout.h"


Widget_ajout::Widget_ajout(FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    name = new QLineEdit("Nouvelle tache");
    name->setMaxLength(100);
    mainlayout->addWidget(name);

    //parent = new QLabel("En attente");
    date = new QLabel();
    timeleft = new QLabel("A faire");
    type = new QLabel();

    // Bouton Nouveau
    QPushButton * boutonAjout = new QPushButton("Ajouter");
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(addTache()));
}

Widget_ajout::~Widget_ajout()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_ajout::addTache()
{
    //Tache * maTache = new Tache(uneTache);
    // data : ajout de maTache dans le modele...
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,name->text());
    firstW->arbo->addTopLevelItem(item);
}
