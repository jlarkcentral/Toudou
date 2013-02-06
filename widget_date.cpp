#include "widget_date.h"

widget_date::widget_date(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    // Boutons choix date absolue/relative
    QWidget * choicewidget = new QWidget();
    QHBoxLayout * choicelayout = new QHBoxLayout();
    QRadioButton * dateabs = new QRadioButton("Date précise",this);
    choicelayout->addWidget(dateabs);
    QRadioButton * daterel = new QRadioButton("Date relative à une autre tâche");
    choicelayout->addWidget(daterel);
    choicewidget->setLayout(choicelayout);
    mainlayout->addWidget(choicewidget);

    // Choix abs
    abswidget = new QWidget();
    QFormLayout * abslayout = new QFormLayout();
    QCalendarWidget * calendar = new QCalendarWidget();
    abslayout->addRow("Date :",calendar);
    QTimeEdit * time = new QTimeEdit();
    abslayout->addRow("Heure :",time);
    abswidget->setLayout(abslayout);
    mainlayout->addWidget(abswidget);
    abswidget->setVisible(false);

    // Choix rel
    relwidget = new QWidget();
    QFormLayout * rellayout = new QFormLayout();


    // Connect boutons choix -- widget correspondant
    QObject::connect(dateabs,SIGNAL(clicked()),this,SLOT(afficher_abs()));
    QObject::connect(daterel,SIGNAL(clicked()),this,SLOT(afficher_rel()));

    // Bouton date absolue choisi par défaut
    dateabs->click();
}

widget_date::~widget_date()
{

}


// SLOTS

void widget_date::afficher_abs()
{
    abswidget->setVisible(true);
}


void widget_date::afficher_rel()
{
    abswidget->setVisible(false);
}
