
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
    details_aff = false;

    // seul le widget_ajout a le focus
    firstW->setDisabled(true);

    // Layout du widget ajout
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    this->setWindowTitle("Ajout d'une tache");
    this->setFixedWidth(300);
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
    name = new QLineEdit("Nouvelle tache");
    name->setMaxLength(100);
    mainlayout->addWidget(nameLabel);
    mainlayout->addWidget(name);

    //parent = new QLabel("En attente");

    // layout pour la date : afficher avec un dÃ©rouleur
    QVBoxLayout * dateLayout = new QVBoxLayout();
    date = new QLabel("Date");
    dateLayout->addWidget(date);
    calendar = new QCalendarWidget();
    dateLayout->addWidget(calendar);
    //mainlayout->addLayout(dateLayout);

    // idem pour preconditions

    timeleft = new QLabel("A faire");
    type = new QLabel();

    // Bouton Nouveau
    QPushButton * boutonAjout = new QPushButton("Ajouter");
    mainlayout->addWidget(boutonAjout);
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(addTache()));
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(close()));

    // essais toolbox
    /*QWidget * details_date = new QWidget();
    details_date->setLayout(dateLayout);
    QToolBox * tools = new QToolBox();
    tools->addItem(details_date,"Détails date");
    mainlayout->addWidget(tools);*/

    // menu dépliable
    QWidget * widget_details = new QWidget();
    QHBoxLayout * layout_details = new QHBoxLayout();
    details = new QPushButton("+");
    details->setFixedWidth(20);
    layout_details->addWidget(details);
    QLabel * afficher = new QLabel("Options avancées");
    layout_details->addWidget(afficher);
    widget_details->setLayout(layout_details);
    mainlayout->addWidget(widget_details);

    QObject::connect(details,SIGNAL(clicked()),this,SLOT(afficherDate()));

    // essais groupbox
    groupbox_date = new QGroupBox("Gestion de date");
    groupbox_date->setLayout(dateLayout);
    groupbox_date->setFlat(true);
    groupbox_date->setVisible(false);
    mainlayout->addWidget(groupbox_date);

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));

}

Widget_ajout::~Widget_ajout()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_ajout::addTache()
{

    //Tache * maTache = new Tache(name->text());
    // data : ajout de maTache dans le modele...

    QTreeWidgetItem * item = new QTreeWidgetItem(firstW->currentItem);
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,name->text());
    item->setText(1,calendar->selectedDate().toString());
    item->setText(2,"Heure");

    // en attendant une meilleure solution : l'ajout d'un QPushButton "cache" la colonne cliquable.
    // solution : afficher une icone ?
    item->setText(3,"[+]");
    item->setText(4,"[X]");

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
    std::cout << details_aff << std::endl;
    if (!details_aff)
    {
        groupbox_date->setVisible(true);
        details->setText("-");
        details_aff = true;
    }
    else
    {
        groupbox_date->setVisible(false);
        details->setText("+");
        details_aff = false;
        // TODO : redimensionner la fenêtre
    }
}

void Widget_ajout::closeEvent(QCloseEvent *event)
{
      emit WidgetClosed();
      event->accept();
}
