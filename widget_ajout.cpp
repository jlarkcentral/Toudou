
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

    details_aff = false;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    this->setWindowFlags(Qt::Popup);

    QLabel * nameLabel = new QLabel("Tache : ");
    name = new QLineEdit("Nouvelle tache");
    name->setMaxLength(100);
    mainlayout->addWidget(nameLabel);
    mainlayout->addWidget(name);

    //parent = new QLabel("En attente");

    // layout pour la date : afficher avec un dÃ©rouleur
    QVBoxLayout * dateLayout = new QVBoxLayout();
    date = new QLabel("Date");
    dateLayout->addWidget(date);
    QCalendarWidget * calendar = new QCalendarWidget();
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

}

Widget_ajout::~Widget_ajout()
{}

// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_ajout::addTache()
{
    //Tache * maTache = new Tache(uneTache);
    // data : ajout de maTache dans le modele...
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,name->text());
    firstW->arbo->addTopLevelItem(item);

    // Fermeture de la fenêtre une fois la tâche ajoutée
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
