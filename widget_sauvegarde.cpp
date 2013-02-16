#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QCloseEvent>

#include "widget_sauvegarde.h"


widget_sauvegarde::widget_sauvegarde(FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;

    QGridLayout * sauvGrid = new QGridLayout();
    QLabel * nomFichier = new QLabel("Sauvegarder la liste sous...");
    nomFichierEdit = new QLineEdit();
    QPushButton * ok = new QPushButton("Sauvegarder");
    QPushButton * annuler = new QPushButton("Annuler");

    sauvGrid->addWidget(nomFichier,0,0);
    sauvGrid->addWidget(nomFichierEdit,1,0);
    sauvGrid->addWidget(ok,2,0);
    sauvGrid->addWidget(annuler,2,2);

    this->setLayout(sauvGrid);
    this->setWindowTitle("Sauvegarder sous...");

    // centre le widget
    this->setWindowFlags(Qt::Sheet | Qt::WindowStaysOnTopHint);
    firstW->setDisabled(true);

    QObject::connect(ok,SIGNAL(clicked()),this,SLOT(saveXml()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));
}

widget_sauvegarde::~widget_sauvegarde()
{}

void widget_sauvegarde::closeEvent(QCloseEvent *event)
{
      emit WidgetClosed();
      event->accept();
}

void widget_sauvegarde::saveXml()
{

}
