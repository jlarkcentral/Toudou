#include "widget_date.h"

widget_date::widget_date(FirstWindow * fw, QWidget *parent) :
    QWidget(parent)
{
    FirstW = fw;
    choix = 3;  // De base, une tâche n'a pas de date associée

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    // Boutons choix date absolue/relative
    QWidget * choicewidget = new QWidget();
    QHBoxLayout * choicelayout = new QHBoxLayout();
    QRadioButton * dateabs = new QRadioButton("Date précise",this);
    choicelayout->addWidget(dateabs);
    QRadioButton * daterel = new QRadioButton("Date relative à une autre tâche");
    choicelayout->addWidget(daterel);
    QRadioButton * nodate = new QRadioButton("Aucune date");
    choicelayout->addWidget(nodate);
    choicewidget->setLayout(choicelayout);
    mainlayout->addWidget(choicewidget);

    // Choix abs
    abswidget = new QWidget();
    QFormLayout * abslayout = new QFormLayout();
    calendar = new QCalendarWidget();
    abslayout->addRow("Date :",calendar);
    time = new QTimeEdit();
    abslayout->addRow("Heure :",time);
    abswidget->setLayout(abslayout);
    mainlayout->addWidget(abswidget);
    abswidget->setVisible(false);

    // Choix rel
    relwidget = new QWidget();
    QGridLayout * rellayout = new QGridLayout();
    spin = new QSpinBox();
    spin->setMinimum(1);
    spin->setMaximum(12);
    rellayout->addWidget(spin,0,0);
    unit = new QComboBox();
    unit->addItem("minute(s)");
    unit->addItem("heure(s)");
    unit->addItem("jour(s)");
    unit->addItem("semaine(s)");
    unit->addItem("mois");
    rellayout->addWidget(unit,0,1);
    avapr = new QComboBox();
    avapr->addItem("avant");
    avapr->addItem("après");
    rellayout->addWidget(avapr,0,2);
    // Tree
    tree = new QTreeWidget();
    QHeaderView * header = tree->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setResizeMode(0,QHeaderView::Stretch);
    header->setResizeMode(3,QHeaderView::Fixed);
    header->setResizeMode(4,QHeaderView::Fixed);
    header->setStretchLastSection(false);
    tree->setHeaderHidden(true);
    tree->setMouseTracking(true);
    tree->setStyleSheet("font-weight : bold; font-size : 18px; ");
    for(int i=0 ; i<FirstW->arbo->topLevelItemCount() ; i++){
        QTreeWidgetItem * itemCourant = FirstW->arbo->topLevelItem(i);
        QTreeWidgetItem * toAdd = itemCourant->clone();
        toAdd->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        tree->addTopLevelItem(toAdd);
    }
    //
    rellayout->addWidget(tree,1,0,1,3);
    relwidget->setLayout(rellayout);
    mainlayout->addWidget(relwidget);
    relwidget->setVisible(false);

    // Connect boutons choix -- widget correspondant
    QObject::connect(dateabs,SIGNAL(clicked()),this,SLOT(afficher_abs()));
    QObject::connect(daterel,SIGNAL(clicked()),this,SLOT(afficher_rel()));
    QObject::connect(nodate,SIGNAL(clicked()),this,SLOT(afficher_rien()));

    // Bouton date absolue choisi par défaut
    dateabs->click();

    // Connect modification date
    QObject::connect(calendar,SIGNAL(selectionChanged()),this,SLOT(date_modifiee()));
    QObject::connect(time,SIGNAL(timeChanged(QTime)),this,SLOT(date_modifiee()));
}

widget_date::~widget_date()
{

}

QDateTime widget_date::getDate()
{
    return date;
}

void widget_date::setDate(QDateTime d)
{
    date = d;
}

bool widget_date::hasDate()
{
    return (choix != 3);
}


// SLOTS

void widget_date::afficher_abs()
{
    abswidget->setVisible(true);
    relwidget->setVisible(false);
    choix = 1;
}


void widget_date::afficher_rel()
{
    abswidget->setVisible(false);
    relwidget->setVisible(true);
    choix = 2;
}

void widget_date::afficher_rien()
{
    abswidget->setVisible(false);
    relwidget->setVisible(false);
    choix = 3;
}

void widget_date::date_modifiee()
{
    if(choix == 1)
    {
        date.setDate(calendar->selectedDate());
        date.setTime(time->time());
    }
    else
    {

    }
}
