
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
    this->setFixedHeight(200);

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);


    // Titre pour le champ nom de la Tache - "tache" ou "sous tache de XXX"
    QLabel * nameLabel;
    if (firstW->currentItem == firstW->arbo->invisibleRootItem()){
        nameLabel = new QLabel("Nouvelle tache : ");
    }
    else{
        nameLabel = new QLabel("Sous-tache de <b>" + firstW->currentItem->text(0) + "</b> :");
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
    date_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    date_plus->setFixedWidth(20);
    date_plus->setToolTip("Définir une date limite pour la tache");
    layout_date_plus->addWidget(date_plus);
    afficher_date = new QLabel("Ajouter une échéance");
    layout_date_plus->addWidget(afficher_date);
    widget_date_plus->setLayout(layout_date_plus);
    mainlayout->addWidget(widget_date_plus);

    dates = new widget_date(firstW);
    mainlayout->addWidget(dates);
    dates->setVisible(false);

    QObject::connect(date_plus,SIGNAL(clicked()),this,SLOT(afficherDate()));
    QObject::connect(dates->nodatebut,SIGNAL(clicked()),this,SLOT(afficherDate()));

    // Bouton Annuler
    QWidget * buttonsWidget = new QWidget();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    boutonAnnul = new QPushButton("Annuler");
    boutonAnnul->setStyleSheet("QPushButton {background : #C60800 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;}");
    buttonsLayout->addWidget(boutonAnnul);

    // Bouton Nouveau
    boutonAjout = new QPushButton("Ajouter");
    boutonAjout->setDisabled(true);
    boutonAjout->setStyleSheet("QPushButton {background : #3A9D23 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;}");
    buttonsLayout->addWidget(boutonAjout);
    buttonsWidget->setLayout(buttonsLayout);
    mainlayout->addWidget(buttonsWidget);

    QObject::connect(boutonAnnul,SIGNAL(clicked()),this,SLOT(close()));
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
        item->setText(1,dates->getDateabs().toString());
        item->setTextColor(1,QColor(152,152,152));
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
        newtache->setDate(1);
    }
    else if(dates->typeDate() == 2)
    {
        newtache->setDaterel(dates->getDaterel());
        newtache->setDate(2);
    }
    else newtache->setDate(3);

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
        this->setFixedHeight(200);
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
