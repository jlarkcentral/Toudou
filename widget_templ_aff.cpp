#include "widget_templ_aff.h"

widget_templ_aff::widget_templ_aff(FirstWindow * fw, QWidget *parent) :
    QWidget(parent)
{
    FirstW = fw;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    QLabel * explications = new QLabel();
    explications->setWordWrap(true);
    explications->setText("Sélectionnez une de vos tâches pré-enregistrées. Votre nouvelle tâche aura alors le même squelette (même nom et même sous-tâches).");
    mainlayout->addWidget(explications);

    tree = new QTreeWidget();
    QHeaderView * header = tree->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setResizeMode(0,QHeaderView::Stretch);
    header->setResizeMode(3,QHeaderView::Fixed);
    header->setResizeMode(4,QHeaderView::Fixed);
    header->setStretchLastSection(false);
    tree->setHeaderHidden(true);
    tree->setMouseTracking(true);
    tree->setStyleSheet("font-weight : bold; font-size : 18px; ");
    for(int i=0 ; i<FirstW->arbo->topLevelItemCount() ; i++){
        QTreeWidgetItem * itemCourant = FirstW->arbo->topLevelItem(i);
        QTreeWidgetItem * toAdd = itemCourant->clone();
        toAdd->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        tree->addTopLevelItem(toAdd);
    }
    mainlayout->addWidget(tree);
}

widget_templ_aff::~widget_templ_aff()
{

}
