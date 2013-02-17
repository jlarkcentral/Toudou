
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolBox>
#include <QGroupBox>
#include <QTreeWidgetItem>

#include "widget_ajout.h"


Widget_ajout::Widget_ajout(FirstWindow *fw,QWidget *parent) :
    QWidget(parent)
{
    // attributs utiles
    firstW = fw;

    date_aff = false;

    // seul le widget_ajout a le focus
    firstW->setDisabled(true);

    // Layout du widget ajout
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    this->setWindowTitle("Ajout d'une tache");
    this->setFixedWidth(300);
    this->setFixedHeight(150);

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);


    // Titre pour le champ nom de la Tache - "tache" ou "sous tache de XXX"
    QLabel * nameLabel;
    if (firstW->currentItem == firstW->arbo->invisibleRootItem()){
        nameLabel = new QLabel("Nouvelle tache : ");
    }
    else{
        nameLabel = new QLabel("Sous-tache de " + firstW->currentItem->text(0) + " :");
    }
    name = new QLineEdit();
    name->setMaxLength(100);
    name->setPlaceholderText("Nouvelle tache");
    mainlayout->addWidget(nameLabel);
    mainlayout->addWidget(name);
    QObject::connect(name,SIGNAL(textEdited(QString)),this,SLOT(textEdited(QString)));

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

    dates = new widget_date(firstW);
    mainlayout->addWidget(dates);
    dates->setVisible(false);

    QObject::connect(date_plus,SIGNAL(clicked()),this,SLOT(afficherDate()));
    QObject::connect(dates->nodatebut,SIGNAL(clicked()),this,SLOT(afficherDate()));

    // Bouton Nouveau
    boutonAjout = new QPushButton("Ajouter");
    boutonAjout->setDisabled(true);
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(addTache()));
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(addTache()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(close()));

    // essais groupbox
    /*groupbox_date = new QGroupBox("Gestion de date");
    groupbox_date->setLayout(dateLayout);
    groupbox_date->setFlat(true);
    groupbox_date->setVisible(false);
    mainlayout->addWidget(groupbox_date);*/

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));

}

Widget_ajout::~Widget_ajout()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_ajout::addTache()
{
    QTreeWidgetItem * item = new QTreeWidgetItem(firstW->currentItem);
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,name->text());
    if (dates->typeDate() == 1){
        item->setText(1,dates->getDateabs().date().toString());
        item->setTextColor(1,QColor(152,152,152));
        item->setText(2,dates->getDateabs().time().toString());
        item->setTextColor(2, QColor(125,125,125));
    }
    if (dates->typeDate() == 2)
    {
        item->setText(1,QString(dates->getDaterel().c_str()));
        item->setTextColor(1,QColor(152,152,152));
    }

    firstW->arbo->addTopLevelItem(item);


    // ajout de la tache dans le modele
    Tache * newtache = new Tache(name->text().toStdString());
    //TODOnewtache->setDate("Date");
    if(dates->typeDate() == 1)
    {
        newtache->setDateabs(dates->getDateabs());
    }
    if(dates->typeDate() == 2)
    {
        newtache->setDaterel(dates->getDaterel());
    }

    newtache->setMatchingItem(item);
    firstW->currentTache->addSousTache(newtache);

    // Fermeture de la fenêtre une fois la tâche ajoutée
    firstW->currentTache = firstW->racine;
    firstW->currentItem = firstW->arbo->invisibleRootItem();
    firstW->setDisabled(false);
    this->close();
}

void Widget_ajout::afficherDate()
{
    if (!date_aff)
    {
        dates->setVisible(true);
        date_plus->setText("-");
        date_aff = true;
        this->setFixedHeight(500);
        this->setFixedWidth(600);
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

void Widget_ajout::closeEvent(QCloseEvent *event)
{
      emit WidgetClosed();
      event->accept();
}

// desactiver le bouton Ajouter quand le nom de la tache est vide
void Widget_ajout::textEdited(QString s)
{
    if (s != ""){
        boutonAjout->setEnabled(true);
    }
    else {
        boutonAjout->setEnabled(false);
    }
}
