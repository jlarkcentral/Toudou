#include <QVBoxLayout>

#include "widget_infos.h"

Widget_infos::Widget_infos(Tache * t, QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    name = new QLabel(QString::fromStdString(t->getNom()));
    //parent = new QLabel("En attente");
    date = new QLabel(QString::fromStdString(t->getDate()));
    timeleft = new QLabel("A faire");
    type = new QLabel();
    if(t->getSousTaches().empty())
    {
        setType("");
    }
    else
    {
        setType("Liste de tches");
    }

    name->setStyleSheet("font-weight : bold; font-size : 18px; ");

    mainlayout->addWidget(name);
    //mainlayout->addWidget(parent);
    mainlayout->addWidget(date);
    mainlayout->addWidget(timeleft);
    mainlayout->addWidget(type);


    // Bouton Nouveau
    QPushButton * boutonAjout = new QPushButton("Ajouter");
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),parent,SLOT(closeDrawer()));
}

Widget_infos::~Widget_infos()
{

}

QLabel* Widget_infos::getName(){return name;}
QLabel* Widget_infos::getParent(){return parent;}
QLabel* Widget_infos::getDate(){return date;}
QLabel* Widget_infos::getTimeleft(){return timeleft;}
QLabel* Widget_infos::getType(){return type;}

void Widget_infos::setName(string s){name->setText(QString::fromStdString(s));}
void Widget_infos::setParent(string s){parent->setText(QString::fromStdString(s));}
void Widget_infos::setDate(string s){date->setText(QString::fromStdString(s));}
void Widget_infos::setTimeleft(string s){timeleft->setText(QString::fromStdString(s));}
void Widget_infos::setType(string s){type->setText(QString::fromStdString(s));}
