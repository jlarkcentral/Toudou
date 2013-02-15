#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include "widget_sauvegarde.h"


widget_sauvegarde::widget_sauvegarde(FirstWindow *fw, QWidget *parent) :
    QWidget(parent)
{
    firstW = fw;

    QGridLayout * sauvGrid = new QGridLayout();
    QLabel * nomFichier = new QLabel("Sauvegarder la liste sous...");
    QLineEdit * nomFichierEdit = new QLineEdit();
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

    QObject::connect(this,SIGNAL(WidgetClosed()),firstW,SLOT(resetDisable()));
}
