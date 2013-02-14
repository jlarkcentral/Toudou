
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
    //parent = new QLabel("En attente");


    // layout pour la date : afficher avec un dÃ©rouleur
    /*QVBoxLayout * dateLayout = new QVBoxLayout();
    date = new QLabel("Date");
    dateLayout->addWidget(date);
    calendar = new QCalendarWidget();
    dateLayout->addWidget(calendar);*/
    //mainlayout->addLayout(dateLayout);

    // idem pour preconditions

    timeleft = new QLabel("A faire");
    type = new QLabel();

    // Bouton Nouveau
    boutonAjout = new QPushButton("Ajouter");
    boutonAjout->setDisabled(true);
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
    if (date_aff){
        item->setText(1,"Date");
        item->setTextColor(1,QColor(152,152,152));
        item->setText(2,"Heure");
        item->setTextColor(2, QColor(125,125,125));
    }

    // en attendant une meilleure solution : l'ajout d'un QPushButton "cache" la colonne cliquable.
    // solution : afficher une icone ?
    //item->setText(3,"[+]");
    //item->
    //item->setText(4,"[X]");


    //QPushButton * plus = new QPushButton("+");
    //plus->setStyleSheet("background-image : url(img/plus.png); background-repeat : no-repeat");
    //plus->setAutoFillBackground(true);
    //plus->setFixedWidth(34);

    //QPushButton * suppr = new QPushButton("X");
    //suppr->setAutoFillBackground(true);
    //suppr->setFixedWidth(34);

    firstW->arbo->addTopLevelItem(item);
    //firstW->arbo->setItemWidget(item,3,plus);
    //firstW->arbo->setItemWidget(item,4,suppr);

    // Fermeture de la fenêtre une fois la tâche ajoutée
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
