
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolBox>
#include <QGroupBox>
#include <QTreeWidgetItem>

#include "widget_modif.h"


Widget_modif::Widget_modif(QTreeWidgetItem * item, FirstWindow *fw,QWidget *parent) :
    QWidget(parent)
{
    // attributs utiles
    firstW = fw;
    itemToModify = item;
    date_aff = false;


    // seul le widget_ajout a le focus
    firstW->setDisabled(true);

    // Layout du widget ajout
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    this->setWindowTitle("Modifier une tache");
    this->setFixedWidth(300);
    this->setFixedHeight(150);

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);


    // Titre pour le champ nom de la Tache - "tache" ou "sous tache de XXX"
    QLabel * nameLabel;
    nameLabel = new QLabel("Modifier " + itemToModify->text(0));
    name = new QLineEdit();
    name->setMaxLength(100);
    name->setText(itemToModify->text(0));
    mainlayout->addWidget(nameLabel);
    mainlayout->addWidget(name);
    QObject::connect(name,SIGNAL(textEdited(QString)),this,SLOT(textEdited(QString)));


    // Bouton Nouveau
    boutonModif = new QPushButton("Modifier");
    mainlayout->addWidget(boutonModif);
    QObject::connect(boutonModif,SIGNAL(clicked()),this,SLOT(modifTache()));
    QObject::connect(boutonModif,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(modifTache()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(close()));

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

    // essais groupbox
    /*groupbox_date = new QGroupBox("Gestion de date");
    groupbox_date->setLayout(dateLayout);
    groupbox_date->setFlat(true);
    groupbox_date->setVisible(false);
    mainlayout->addWidget(groupbox_date);*/

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));

}

Widget_modif::~Widget_modif()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_modif::modifTache()
{
    //QTreeWidgetItem * item = new QTreeWidgetItem(firstW->currentItem);
    //item->setCheckState(0,Qt::Unchecked);

    itemToModify->setText(0,name->text());
    if (date_aff){
        itemToModify->setText(1,dates->getDateabs().toString());
        itemToModify->setTextColor(1,QColor(152,152,152));
    }
    else{
        itemToModify->setText(1,itemToModify->text(1));
        itemToModify->setTextColor(1,QColor(152,152,152));
        itemToModify->setText(2,itemToModify->text(2));
        itemToModify->setTextColor(2, QColor(125,125,125));
    }
    //firstW->arbo->addTopLevelItem(item);


    // ajout de la tache dans le modele
    //Tache * newtache = new Tache(name->text().toStdString());
    //TODOnewtache->setDate("Date");
    //    if(dates->hasDate())
    //    {
    //        newtache->setDate(dates->getDate());
    //    }

    //    newtache->setMatchingItem(item);
    //    firstW->currentTache->addSousTache(newtache);

    // Fermeture de la fenêtre une fois la tâche ajoutée
    firstW->currentTache = firstW->racine;
    firstW->currentItem = firstW->arbo->invisibleRootItem();
    firstW->setDisabled(false);
    this->close();
}

void Widget_modif::afficherDate()
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

void Widget_modif::closeEvent(QCloseEvent *event)
{
    emit WidgetClosed();
    event->accept();
}

// desactiver le bouton Ajouter quand le nom de la tache est vide
void Widget_modif::textEdited(QString s)
{
    if (s != ""){
        boutonModif->setEnabled(true);
    }
    else {
        boutonModif->setEnabled(false);
    }
}
