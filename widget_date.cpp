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
    QVBoxLayout * choicelayout = new QVBoxLayout();
    dateabsbut = new QRadioButton("Date précise",this);
    dateabsbut->setToolTip("Attribuer une date absolue sur le calendrier");
    choicelayout->addWidget(dateabsbut);
    daterelbut = new QRadioButton("Date relative à une autre tâche");
    daterelbut->setToolTip("L'échéance de la tâche dépend d'une autre tâche de la liste");
    choicelayout->addWidget(daterelbut);
    nodatebut = new QRadioButton("Aucune date");
    nodatebut->setToolTip("Pas de date pour cette tâche");
    choicelayout->addWidget(nodatebut);
    choicewidget->setLayout(choicelayout);
    mainlayout->addWidget(choicewidget);

    // Choix abs
    abswidget = new QWidget();
    QHBoxLayout * abslayout = new QHBoxLayout();
    abslayout->addStretch();
    calendar = new QCalendarWidget();
    calendar->setMinimumDate(QDate::currentDate());
    abslayout->addWidget(calendar);
    abslayout->addStretch();
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
        toAdd->setData(0, Qt::CheckStateRole, QVariant());
        FirstW->removeCheckboxes(toAdd);
        tree->addTopLevelItem(toAdd);
    }
    currentItem = tree->topLevelItem(0);
    //
    rellayout->addWidget(tree,1,0,1,3);
    relwidget->setLayout(rellayout);
    mainlayout->addWidget(relwidget);
    relwidget->setVisible(false);

    // Connect boutons choix -- widget correspondant
    QObject::connect(dateabsbut,SIGNAL(clicked()),this,SLOT(afficher_abs()));
    QObject::connect(daterelbut,SIGNAL(clicked()),this,SLOT(afficher_rel()));
    QObject::connect(nodatebut,SIGNAL(clicked()),this,SLOT(afficher_rien()));

    // Bouton date absolue choisi par défaut
    dateabsbut->click();

    // Changement du currentItem lorsqu'on clique sur l'arbre
    QObject::connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(item_modifie(QTreeWidgetItem*)));

    // Connect modification date
    QObject::connect(calendar,SIGNAL(selectionChanged()),this,SLOT(date_modifiee()));
    QObject::connect(spin,SIGNAL(valueChanged(int)),this,SLOT(date_modifiee()));
    QObject::connect(unit,SIGNAL(currentIndexChanged(int)),this,SLOT(date_modifiee()));
    QObject::connect(avapr,SIGNAL(currentIndexChanged(int)),this,SLOT(date_modifiee()));
    QObject::connect(tree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(date_modifiee()));
}

widget_date::~widget_date()
{

}

QDate widget_date::getDateabs()
{
    return dateabs;
}

void widget_date::setDateabs(QDate d)
{
    dateabs = d;
}

string widget_date::getDaterel()
{
    return daterel;
}

void widget_date::setDaterel(string s)
{
    daterel = s;
}

int widget_date::typeDate()
{
    return choix;
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
    dateabsbut->click();
}

void widget_date::date_modifiee()
{
    if(choix == 1)
    {
        dateabs = calendar->selectedDate();
    }
    if(choix == 2)
    {
        int nb = spin->value();
        QString unite = unit->currentText();
        QString rel = avapr->currentText();
        QString datetache;
        QString nomtache;
        if (currentItem)
        {
            datetache = currentItem->text(1);
            nomtache = currentItem->text(0);
        }
        std::ostringstream oss;
        oss << nb;
        daterel = oss.str() + " " + unite.toStdString() + " " + rel.toStdString() + " " + nomtache.toStdString();
    }
}

void widget_date::item_modifie(QTreeWidgetItem* item)
{
    currentItem = item;
}
