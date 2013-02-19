#include "widget_precond.h"

widget_precond::widget_precond(FirstWindow * fw, QWidget *parent) :
    QWidget(parent)
{
    FirstW = fw;

    QVBoxLayout * mainlayout = new QVBoxLayout();
    this->setLayout(mainlayout);

    QLabel * explications = new QLabel();
    explications->setWordWrap(true);
    explications->setText("Indiquez quelles tâches devront être effectuées avant cette nouvelle tâche. Il est possible d'en spécifier plusieurs.");
    explications->setAlignment(Qt::AlignJustify);
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

    QObject::connect(tree,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(itemChecked(QTreeWidgetItem*,int)));
}


widget_precond::~widget_precond()
{

}

vector<Tache> widget_precond::getPreconditions()
{
    vector<Tache> preconditions;
    for (vector<QTreeWidgetItem*>::iterator it = itemschecked.begin() ; it != itemschecked.end() ; ++it)
    {
        Tache t(*it,false);
        preconditions.push_back(t);
    }
    return preconditions;
}

// SLOTS

void widget_precond::itemChecked(QTreeWidgetItem* item,int n)
{
    if (n == 0)
    {
        if (item->checkState(0)==Qt::Checked)
        {
            itemschecked.push_back(item);
        }
        else
        {
            for (vector<QTreeWidgetItem*>::iterator it = itemschecked.begin() ; it != itemschecked.end() ; ++it)
            {
                if (*it == item)
                {
                    itemschecked.erase(it);
                    break;
                }
            }
        }
    }
}
