
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QToolBox>
#include <QGroupBox>

#include "widget_ajout.h"


Widget_ajout::Widget_ajout(FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;

    date_aff = false;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    //this->setWindowFlags(Qt::Popup);
    this->setWindowTitle("Ajout d'une tache");
    this->setFixedWidth(300);
    this->setFixedHeight(150);

    QLabel * nameLabel = new QLabel("Tache : ");
    name = new QLineEdit("Nouvelle tache");
    name->setMaxLength(100);
    mainlayout->addWidget(nameLabel);
    mainlayout->addWidget(name);

    //parent = new QLabel("En attente");



    // idem pour preconditions

    timeleft = new QLabel("A faire");
    type = new QLabel();

    // Bouton Nouveau
    QPushButton * boutonAjout = new QPushButton("Ajouter");
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(addTache()));
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(close()));

    // menu date  dépliable
    QWidget * widget_date_plus= new QWidget();
    QHBoxLayout * layout_date_plus = new QHBoxLayout();
    date_plus = new QPushButton("+");
    date_plus->setFixedWidth(20);
    layout_date_plus->addWidget(date_plus);
    QLabel * afficher_date = new QLabel("Ajouter une échéance");
    layout_date_plus->addWidget(afficher_date);
    widget_date_plus->setLayout(layout_date_plus);
    mainlayout->addWidget(widget_date_plus);

    dates = new widget_date();
    mainlayout->addWidget(dates);
    dates->setVisible(false);

    QObject::connect(date_plus,SIGNAL(clicked()),this,SLOT(afficherDate()));

    // essais groupbox
    /*groupbox_date = new QGroupBox("Gestion de date");
    groupbox_date->setLayout(dateLayout);
    groupbox_date->setFlat(true);
    groupbox_date->setVisible(false);
    mainlayout->addWidget(groupbox_date);*/

}

Widget_ajout::~Widget_ajout()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_ajout::addTache()
{
    //Tache * maTache = new Tache(uneTache);
    // data : ajout de maTache dans le modele...
    QTreeWidgetItem * item = new QTreeWidgetItem(firstW->itemCourant);
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,name->text());
    item->setText(1,"Date");
    item->setText(2,"Heure");

    QPushButton * plus = new QPushButton("+");
    //plus->setStyleSheet("background-image : url(img/plus.png); background-repeat : no-repeat");
    plus->setAutoFillBackground(true);
    //plus->setFixedWidth(34);

    QPushButton * suppr = new QPushButton("X");
    suppr->setAutoFillBackground(true);
    //suppr->setFixedWidth(34);

    firstW->arbo->addTopLevelItem(item);
    firstW->arbo->setItemWidget(item,3,plus);
    firstW->arbo->setItemWidget(item,4,suppr);
    QObject::connect(plus,SIGNAL(clicked()),firstW,SLOT(popAjout()));
    QObject::connect(plus,SIGNAL(clicked()),firstW,SLOT(popAjout()));

    // Fermeture de la fenêtre une fois la tâche ajoutée
    this->close();
}

void Widget_ajout::afficherDate()
{
    if (!date_aff)
    {
        dates->setVisible(true);
        date_plus->setText("-");
        date_aff = true;
        this->setFixedHeight(600);
        this->setFixedWidth(500);
    }
    else
    {
        dates->setVisible(false);
        date_plus->setText("+");
        date_aff = false;
        this->setFixedHeight(150);
        this->setFixedWidth(300);
    }
}
