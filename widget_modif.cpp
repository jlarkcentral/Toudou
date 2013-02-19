
#include <QVBoxLayout>
#include <QLineEdit>
#include <QToolBox>
#include <QGroupBox>
#include <QTreeWidgetItem>

#include "widget_modif.h"


Widget_modif::Widget_modif(QTreeWidgetItem *item,FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    // attributs utiles
    firstW = fw;
    itemToModify = item;

    date_aff = false;
    precond_aff = false;
    ordon_aff = false;
    template_aff = false;

    // seul le widget_ajout a le focus
    firstW->setDisabled(true);

    // Layout du widget ajout
    QGridLayout * mainlayout = new QGridLayout();
    this->setLayout(mainlayout);
    this->setWindowTitle("Ajout d'une tâche");
    this->setFixedWidth(350);
    this->setFixedHeight(300);

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);

    mainlayout->setRowStretch(12,5);

    // Titre pour le champ nom de la Tache - "tache" ou "sous tache de XXX"
    QLabel * nameLabel;
    nameLabel = new QLabel("Modification de <b>" + itemToModify->text(0) + "</b> :");
    name = new QLineEdit();
    name->setMaxLength(100);
    name->setFixedHeight(50);
    name->setStyleSheet("QLineEdit{font-size : 18px;}");
    name->setText(itemToModify->text(0));
    mainlayout->addWidget(nameLabel,0,0,1,2);
    mainlayout->addWidget(name,1,0,1,2);
    QObject::connect(name,SIGNAL(textEdited(QString)),this,SLOT(textEdited(QString)));


    // menu date  dépliable
    date_plus = new QPushButton("+");
    date_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    date_plus->setFixedWidth(20);
    date_plus->setToolTip("Définir une date limite pour la tâche");
    mainlayout->addWidget(date_plus,2,0);
    afficher_date = new QLabel("Ajouter une échéance");
    mainlayout->addWidget(afficher_date,2,1);

    // menu précond dépliable
    precond_plus = new QPushButton("+");
    precond_plus->setStyleSheet("QPushButton {font-weight : bold;}");
    precond_plus->setFixedWidth(20);
    precond_plus->setToolTip("Indiquer si certaines tâches doivent être réalisées avant celles-ci");
    mainlayout->addWidget(precond_plus,3,0);
    afficher_precond = new QLabel("Ajouter une ou des précondition(s)");
    mainlayout->addWidget(afficher_precond,3,1);

    QFrame* line = new QFrame();
    line->setGeometry(QRect(/* ... */));
    line->setFrameShape(QFrame::HLine); // Replace by VLine for vertical line
    line->setFrameShadow(QFrame::Sunken);
    mainlayout->addWidget(line,6,0,1,2);


    // Widgets dÃ©pliables
    dates = new widget_date(firstW);
    mainlayout->addWidget(dates,7,0,1,2);
    dates->setVisible(false);

    QObject::connect(date_plus,SIGNAL(clicked()),this,SLOT(afficherDate()));
    QObject::connect(dates->nodatebut,SIGNAL(clicked()),this,SLOT(afficherDate()));

    preconds = new widget_precond(firstW);
    mainlayout->addWidget(preconds,8,0,1,2);
    preconds->setVisible(false);

    QObject::connect(precond_plus,SIGNAL(clicked()),this,SLOT(afficherPrecond()));

    //mainlayout->addStretch();

    // Bouton Annuler
    QWidget * buttonsWidget = new QWidget();
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    boutonAnnul = new QPushButton("Annuler");
    boutonAnnul->setStyleSheet("QPushButton {background : #C60800 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;}");
    boutonAnnul->setFixedWidth(130);
    buttonsLayout->addWidget(boutonAnnul);

    // Bouton Nouveau
    boutonAjout = new QPushButton("Ajouter");
    boutonAjout->setStyleSheet("QPushButton {background : #3A9D23 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;} QPushButton:disabled{background : #CECECE;}");
    boutonAjout->setFixedWidth(130);
    buttonsLayout->addWidget(boutonAjout);
    buttonsWidget->setLayout(buttonsLayout);
    mainlayout->addWidget(buttonsWidget,12,0,1,2);

    QObject::connect(boutonAnnul,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(addTache()));
    QObject::connect(boutonAjout,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(addTache()));
    QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(close()));

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));

}

Widget_modif::~Widget_modif()
{}



// fonction d ajout dans le modele et dans l arborescence de la nouvelle tache
void Widget_modif::addTache()
{
    if(name->text()!=""){


        firstW->defineCurrentTache(itemToModify->parent(),firstW->racine);

        bool ordre = firstW->currentTache->getOrdon();
        int numberOrd = firstW->currentTache->getSousTaches().size() + 1;

        itemToModify->setCheckState(0,Qt::Unchecked);
        if(ordre){

            ostringstream number;
            number << numberOrd;
            string numberString = number.str();

            itemToModify->setText(0,QString(numberString.c_str())+". "+name->text());
        }
        else itemToModify->setText(0,name->text());
        if (dates->typeDate() == 1){
            itemToModify->setText(1,dates->getDateabs().toString());
            itemToModify->setTextColor(1,QColor(152,152,152));
        }
        if (dates->typeDate() == 2)
        {
            itemToModify->setText(1,QString(dates->getDaterel().c_str()));
            itemToModify->setTextColor(1,QColor(152,152,152));
        }


        // ajout de la tache dans le modele
        firstW->defineCurrentTache(itemToModify,firstW->racine);
        //TODOnewtache->setDate("Date");
        if(dates->typeDate() == 1)
        {
            firstW->currentTache->setDateabs(dates->getDateabs());
            firstW->currentTache->setDate(1);
        }
        else if(dates->typeDate() == 2)
        {
            firstW->currentTache->setDaterel(dates->getDaterel());
            firstW->currentTache->setDate(2);
        }
        else firstW->currentTache->setDate(3);
        firstW->currentTache->setPreconditions(preconds->getPreconditions());


        // AJOUT avec template

//        if(firstW->checkedItem(firstW->templatesTree)){
//            cout << "check" << endl;
//            QTreeWidgetItem * checkedItemClone = firstW->checkedItem(firstW->templatesTree)->clone();
//            item->addChild(checkedItemClone);
//        }

        // Fermeture de la fenêtre une fois la tâche ajoutée
        firstW->currentTache = firstW->racine;
        firstW->currentItem = firstW->arbo->invisibleRootItem();
        firstW->setDisabled(false);
        this->close();
    }
}

void Widget_modif::afficherDate()
{
    if (!date_aff)
    {
        dates->setVisible(true);
        date_plus->setText("-");
        date_aff = true;
        this->setFixedHeight(600);
        this->setFixedWidth(350);

        afficher_date->setStyleSheet("QLabel{font-weight : bold;}");

        if (precond_aff)
        {
            preconds->setVisible(false);
            precond_plus->setText("+");
            precond_aff = false;
            afficher_precond->setStyleSheet("");
        }
        if (ordon_aff)
        {
            ordon_expl->setVisible(false);
            ordon->setVisible(false);
            ordon_plus->setText("+");
            ordon_aff = false;
            afficher_ordon->setStyleSheet("");
        }
        if (template_aff)
        {
            templ->setVisible(false);
            template_plus->setText("+");
            template_aff = false;
            afficher_template->setStyleSheet("");
        }
    }
    else
    {
        dates->setVisible(false);
        date_plus->setText("+");
        date_aff = false;
        this->setFixedHeight(300);
        this->setFixedWidth(350);
        afficher_date->setStyleSheet("");
    }
}

void Widget_modif::afficherPrecond()
{
    if (!precond_aff)
    {
        preconds->setVisible(true);
        precond_plus->setText("-");
        precond_aff = true;
        this->setFixedHeight(600);
        afficher_precond->setStyleSheet("QLabel{font-weight : bold;}");
        if (date_aff)
        {
            dates->setVisible(false);
            date_plus->setText("+");
            date_aff = false;
            this->setFixedWidth(350);
            afficher_date->setStyleSheet("");
        }
        if (ordon_aff)
        {
            ordon_expl->setVisible(false);
            ordon->setVisible(false);
            ordon_plus->setText("+");
            ordon_aff = false;
            afficher_ordon->setStyleSheet("");
        }
        if (template_aff)
        {
            templ->setVisible(false);
            template_plus->setText("+");
            template_aff = false;
            afficher_template->setStyleSheet("");
        }
    }
    else
    {
        preconds->setVisible(false);
        precond_plus->setText("+");
        precond_aff = false;
        this->setFixedHeight(300);
        afficher_precond->setStyleSheet("");
    }
}

void Widget_modif::afficherOrdon()
{
    if (!ordon_aff)
    {
        ordon_expl->setVisible(true);
        ordon->setVisible(true);
        ordon_plus->setText("-");
        ordon_aff = true;
        this->setFixedHeight(450);
        afficher_ordon->setStyleSheet("QLabel{font-weight : bold;}");
        if (date_aff)
        {
            dates->setVisible(false);
            date_plus->setText("+");
            date_aff = false;
            this->setFixedWidth(350);
            afficher_date->setStyleSheet("");
        }
        if (precond_aff)
        {
            preconds->setVisible(false);
            precond_plus->setText("+");
            precond_aff = false;
            afficher_precond->setStyleSheet("");
        }
        if (template_aff)
        {
            templ->setVisible(false);
            template_plus->setText("+");
            template_aff = false;
            afficher_template->setStyleSheet("");
        }
    }
    else
    {
        ordon_expl->setVisible(false);
        ordon->setVisible(false);
        ordon_plus->setText("+");
        ordon_aff = false;
        this->setFixedHeight(300);
        afficher_ordon->setStyleSheet("");
    }
}

void Widget_modif::afficherTempl()
{
    if (!template_aff)
    {
        templ->setVisible(true);
        template_plus->setText("-");
        template_aff = true;
        this->setFixedHeight(600);
        afficher_template->setStyleSheet("QLabel{font-weight : bold;}");
        if (date_aff)
        {
            dates->setVisible(false);
            date_plus->setText("+");
            date_aff = false;
            this->setFixedWidth(350);
            afficher_date->setStyleSheet("");
        }
        if (precond_aff)
        {
            preconds->setVisible(false);
            precond_plus->setText("+");
            precond_aff = false;
            afficher_precond->setStyleSheet("");
        }
        if (ordon_aff)
        {
            ordon_expl->setVisible(false);
            ordon->setVisible(false);
            ordon_plus->setText("+");
            ordon_aff = false;
            afficher_ordon->setStyleSheet("");
        }
    }
    else
    {
        templ->setVisible(false);
        template_plus->setText("+");
        template_aff = false;
        this->setFixedHeight(300);
        afficher_template->setStyleSheet("");
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
        boutonAjout->setEnabled(true);
    }
    else {
        boutonAjout->setEnabled(false);
    }
}
