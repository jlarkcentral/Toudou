#include "widget_templ_aff.h"

widget_templ_aff::widget_templ_aff(FirstWindow * fw, QWidget *parent) :
    QWidget(parent)
{
    FirstW = fw;

    hasTempl = false;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    QLabel * explications = new QLabel();
    explications->setWordWrap(true);
    explications->setText("S�lectionnez une de vos t�ches pr�-enregistr�es. Votre nouvelle t�che aura alors le m�me squelette (m�me nom et m�me sous-t�ches).");
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
    for(int i=0 ; i<FirstW->templatesTree->topLevelItemCount() ; i++){
    // ICI
        QTreeWidgetItem * itemCourant = FirstW->templatesTree->topLevelItem(i);
        QTreeWidgetItem * toAdd = itemCourant->clone();
        FirstW->disableSubtasks(toAdd);
        toAdd->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        tree->addTopLevelItem(toAdd);
    }
    mainlayout->addWidget(tree);

    QObject::connect(tree,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(itemChecked(QTreeWidgetItem*,int)));
}

widget_templ_aff::~widget_templ_aff()
{

}

QTreeWidgetItem * widget_templ_aff::getTempl()
{
    for (int i=0 ; i<tree->topLevelItemCount() ; ++i)
    {
        if (tree->topLevelItem(i)->checkState(0) == Qt::Checked)
        {
            return tree->topLevelItem(i);
        }
    }
}

bool widget_templ_aff::hasTemplate()
{
    return hasTempl;
}


// SLOTS

void widget_templ_aff::itemChecked(QTreeWidgetItem* item, int n)
{
    if (n == 0)
    {
        if (item->checkState(0)==Qt::Checked)
        {
            for (int i = 0 ; i<tree->topLevelItemCount() ; ++i)
            {
                if (tree->topLevelItem(i) != item)
                {
                    tree->topLevelItem(i)->setCheckState(0,Qt::Unchecked);
                }
            }
            hasTempl = true;
        }
        else
        {
            hasTempl = false;
        }
    }
}
