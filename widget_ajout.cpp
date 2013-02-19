
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
    precond_aff = false;
    ordon_aff = false;

    // seul le widget_ajout a le focus
    firstW->setDisabled(true);

    // Layout du widget ajout
    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);
    this->setWindowTitle("Ajout d'une tache");
    this->setFixedWidth(350);
    this->setFixedHeight(300);

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
    afficher_date = new QLabel("<b>Ajouter une échéance</b>");
    layout_date_plus->addWidget(afficher_date);
    widget_date_plus->setLayout(layout_date_plus);
    mainlayout->addWidget(widget_date_plus);

    // menu précond dépliable
    QWidget * widget_precond_plus = new QWidget();
    QHBoxLayout * layout_precond_plus = new QHBoxLayout();
    precond_plus = new QPushButton("+");
    precond_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    precond_plus->setFixedWidth(20);
    precond_plus->setToolTip("Indiquer si certaines taches doivent être réalisées avant celles-ci");
    layout_precond_plus->addWidget(precond_plus);
    afficher_precond = new QLabel("<b>Ajouter une ou des précondition(s)</b>");
    layout_precond_plus->addWidget(afficher_precond);
    widget_precond_plus->setLayout(layout_precond_plus);
    mainlayout->addWidget(widget_precond_plus);

    // menu liste ordonnee dépliable
    QWidget * widget_ordon_plus = new QWidget();
    QHBoxLayout * layout_ordon_plus = new QHBoxLayout();
    ordon_plus = new QPushButton("+");
    ordon_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    ordon_plus->setFixedWidth(20);
    ordon_plus->setToolTip("Avec cette option, toutes les sous-taches seront classées dans un ordre précis");
    layout_ordon_plus->addWidget(ordon_plus);
    afficher_ordon = new QLabel("<b>Ajouter l'option de liste ordonnée</b>");
    layout_ordon_plus->addWidget(afficher_ordon);
    widget_ordon_plus->setLayout(layout_ordon_plus);
    mainlayout->addWidget(widget_ordon_plus);

    // menu template dépliable
    QWidget * widget_template_plus = new QWidget();
    QHBoxLayout * layout_template_plus = new QHBoxLayout();
    template_plus = new QPushButton("+");
    template_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    template_plus->setFixedWidth(20);
    template_plus->setToolTip("Charger un type de tâche préalablement enregistré");
    layout_template_plus->addWidget(template_plus);
    afficher_template = new QLabel("<b> Charger une tâche enregistrée");
    layout_template_plus->addWidget(afficher_template);
    widget_template_plus->setLayout(layout_template_plus);
    mainlayout->addWidget(widget_template_plus);

    //mainlayout->addStretch();

    // Widgets dépliables
    dates = new widget_date(firstW);
    mainlayout->addWidget(dates);
    dates->setVisible(false);

    QObject::connect(date_plus,SIGNAL(clicked()),this,SLOT(afficherDate()));
    QObject::connect(dates->nodatebut,SIGNAL(clicked()),this,SLOT(afficherDate()));

    preconds = new widget_precond(firstW);
    mainlayout->addWidget(preconds);
    preconds->setVisible(false);

    QObject::connect(precond_plus,SIGNAL(clicked()),this,SLOT(afficherPrecond()));

    ordon_expl = new QLabel("En cochant cette option, toutes les sous-tâches seront ordonnées. Ainsi, il faudra effectuer la première sous-tache avant la deuxième, et ainsi de suite...");
    ordon_expl->setWordWrap(true);
    mainlayout->addWidget(ordon_expl);
    ordon_expl->setVisible(false);
    ordon = new QCheckBox("Liste ordonnée");
    mainlayout->addWidget(ordon);
    ordon->setVisible(false);

    QObject::connect(ordon_plus,SIGNAL(clicked()),this,SLOT(afficherOrdon()));

    mainlayout->addStretch();

    // Bouton Annuler
    QWidget * buttonsWidget = new QWidget();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    boutonAnnul = new QPushButton("Annuler");
    boutonAnnul->setStyleSheet("QPushButton {background : #C60800 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;}");
    boutonAnnul->setFixedWidth(130);
    buttonsLayout->addWidget(boutonAnnul);

    // Bouton Nouveau
    boutonAjout = new QPushButton("Ajouter");
    boutonAjout->setDisabled(true);
    boutonAjout->setStyleSheet("QPushButton {background : #3A9D23 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;} QPushButton:disabled{background : #CECECE;}");
    boutonAjout->setFixedWidth(130);
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

    firstW->defineCurrentTache(item->parent(),firstW->racine);

    bool ordre = firstW->currentTache->getOrdon();
    int numberOrd = firstW->currentTache->getSousTaches().size() + 1;

    cout << "currentTache ordonnee : " << ordre << endl;

    item->setCheckState(0,Qt::Unchecked);
    if(ordre){

        ostringstream number;
        number << numberOrd;
        string numberString = number.str();

        item->setText(0,QString(numberString.c_str())+". "+name->text());
    }
    else item->setText(0,name->text());
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
    newtache->setPreconditions(preconds->getPreconditions());
    newtache->afficherPreconds(); // VERIFICATION (test)
    newtache->setOrdon(ordon->isChecked());

    newtache->setMatchingItem(item);
    firstW->defineCurrentTache(item->parent(),firstW->racine);
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
        this->setFixedHeight(600);
        this->setFixedWidth(350);
        if (precond_aff)
        {
            preconds->setVisible(false);
            precond_plus->setText("+");
            precond_aff = false;
        }
        if (ordon_aff)
        {
            ordon_expl->setVisible(false);
            ordon->setVisible(false);
            ordon_plus->setText("+");
            ordon_aff = false;
        }
    }
    else
    {
        dates->setVisible(false);
        date_plus->setText("+");
        date_aff = false;
        this->setFixedHeight(300);
        this->setFixedWidth(350);
    }
}

void Widget_ajout::afficherPrecond()
{
    if (!precond_aff)
    {
        preconds->setVisible(true);
        precond_plus->setText("-");
        precond_aff = true;
        this->setFixedHeight(600);
        if (date_aff)
        {
            dates->setVisible(false);
            date_plus->setText("+");
            date_aff = false;
            this->setFixedWidth(350);
        }
        if (ordon_aff)
        {
            ordon_expl->setVisible(false);
            ordon->setVisible(false);
            ordon_plus->setText("+");
            ordon_aff = false;
        }
    }
    else
    {
        preconds->setVisible(false);
        precond_plus->setText("+");
        precond_aff = false;
        this->setFixedHeight(300);
    }
}

void Widget_ajout::afficherOrdon()
{
    if (!ordon_aff)
    {
        ordon_expl->setVisible(true);
        ordon->setVisible(true);
        ordon_plus->setText("-");
        ordon_aff = true;
        this->setFixedHeight(600);
        if (date_aff)
        {
            dates->setVisible(false);
            date_plus->setText("+");
            date_aff = false;
            this->setFixedWidth(350);
        }
        if (precond_aff)
        {
            preconds->setVisible(false);
            precond_plus->setText("+");
            precond_aff = false;
        }
    }
    else
    {
        ordon_expl->setVisible(false);
        ordon->setVisible(false);
        ordon_plus->setText("+");
        ordon_aff = false;
        this->setFixedHeight(300);
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
