#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QCloseEvent>
#include <QStatusBar>

#include "widget_template.h"


widget_template::widget_template(Tache * tacheRacine,FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;
    root = tacheRacine;

    QGridLayout * sauvGrid = new QGridLayout();
    QLabel * nomFichier = new QLabel("Creer un type de t�che...");
    nomFichierEdit = new QLineEdit();
    QPushButton * ok = new QPushButton("Sauvegarder");
    QPushButton * annuler = new QPushButton("Annuler");

    sauvGrid->addWidget(nomFichier,0,0);
    sauvGrid->addWidget(nomFichierEdit,1,0,1,3);
    sauvGrid->addWidget(ok,2,2);
    sauvGrid->addWidget(annuler,2,0);



    this->setLayout(sauvGrid);
    this->setWindowTitle("Creer un type de tache");

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);
    firstW->setDisabled(true);

    QObject::connect(ok,SIGNAL(clicked()),this,SLOT(saveXml()));
    QObject::connect(nomFichierEdit,SIGNAL(returnPressed()),this,SLOT(saveXml()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));
}

widget_template::~widget_template()
{}

void widget_template::closeEvent(QCloseEvent *event)
{
    emit WidgetClosed();
    event->accept();
}

void widget_template::saveXml()
{
    if(nomFichierEdit->text().toStdString()!=""){
        root->setNom(nomFichierEdit->text().toStdString());
        firstW->templates->addSousTache(root);

        firstW->sauvegarderTemplates();
        firstW->chargerXml("../Toudou/xml/templates.xml",firstW->templatesTree->invisibleRootItem(),firstW->templates);
        firstW->statbar->showMessage("Le type de tache " +nomFichierEdit->text()+ " est maintenant disponible",3000);
    }
    this->close();
}
