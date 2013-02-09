#include <unistd.h>

#include <QLabel>
#include <QTreeWidget>
#include <QPushButton>
#include <QHeaderView>

#include "firstwindow.h"
#include "tache.h"
#include "widget_infos.h"
#include "widget_ajout.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //drawerOpened = false;

    // Taille fenêtre
    setMinimumWidth(400);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    centralwidget->setLayout(mainLayout);

    // Entête fenêtre (title + icon)
    setWindowTitle("Toudou");

    // Titre
    QLabel * title = new QLabel("Gestionnaire de tâches");
    title->setAlignment(Qt::AlignCenter);
    QFont titlefont("LMRomanUnsl10");
    title->setFont(titlefont);
    title->setStyleSheet("font-size : 28px");
    mainLayout->addWidget(title,0,0,1,2);

    // Logo
    QLabel * logo = new QLabel();
    QPixmap logoresource("img/toudou.gif");
    logo->setPixmap(logoresource);
    logo->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logo,1,0,1,2);

    // Onglets
    QTabWidget * onglets = new QTabWidget();
    //onglets->setFixedWidth(400);
    mainLayout->addWidget(onglets,2,0,1,1);

    // TreeWidget
    arbo = new QTreeWidget();
    currentItem = arbo->invisibleRootItem();
    QHeaderView * header = arbo->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setResizeMode(0,QHeaderView::Stretch);
    header->setResizeMode(3,QHeaderView::Fixed);
    header->setResizeMode(4,QHeaderView::Fixed);
    header->setStretchLastSection(false);
    arbo->setHeaderHidden(true);
    arbo->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arbo->setColumnCount(5);

    QObject::connect(arbo,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(popup(QTreeWidgetItem*,int)));
    QObject::connect(arbo,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(tacheChecked(QTreeWidgetItem*,int)));
    // FAIRE UN SLOT POUR RAYER LE TEXTE

    // insertion arbo dans premier onglet
    QWidget * page = new QWidget();
    QVBoxLayout * pagelayout = new QVBoxLayout();
    page->setLayout(pagelayout);
    page->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    pagelayout->addWidget(arbo);
    onglets->addTab(page,"Toutes les tâches");

    // Test second onglet
    QPushButton * testbutton = new QPushButton("Achevées");
    QWidget * page2 = new QWidget();
    QVBoxLayout * pagelayout2 = new QVBoxLayout();
    page2->setLayout(pagelayout2);
    pagelayout2->addWidget(testbutton);
    onglets->addTab(page2,"Achevées");

    // Bouton Nouveau
    QPushButton * newbutton = new QPushButton("Nouveau");
    pagelayout->addWidget(newbutton);
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popup()));


}

FirstWindow::~FirstWindow()
{
}

// popup ajout d une nouvelle tache
void FirstWindow::popup()
{
    currentItem = arbo->invisibleRootItem();
    Widget_ajout * w_a = new Widget_ajout(this);
    w_a->show();
}

// popup ajout ou delete suivant l'endroit du clic sur la tache dans le QTreeWidgetItem
void FirstWindow::popup(QTreeWidgetItem* i,int n)
{
    if (n == 3 ){
        currentItem = i;
        arbo->expandItem(currentItem);
        Widget_ajout * w_a = new Widget_ajout(this);
        w_a->show();
    }
    else if (n == 4){
        currentItem = i;
        // ajouter un popup de confirmation ...
        delete(currentItem);
    }
}

void FirstWindow::resetDisable()
{
    this->setDisabled(false);
}

void FirstWindow::tacheChecked(QTreeWidgetItem * item, int n)
{/*
    if (n==0){
        if (item->checkState(0)==Qt::Checked){
            item->setText(0,"test");
        }
    }*/
}

//void FirstWindow::openDrawer()
//{
//    if (!drawerOpened)
//    {
//        int size = width();
//        for(int i=0 ; i<15 ; i++)
//        {
//            usleep(10000);
//            size += 20;
//            setFixedWidth(size);
//        }

//        // TEST : tâche
//        Tache * t = new Tache("Ma jolie tâche");
//        t->setDate("7 février 2013");
//        t->setFini(false);

//        Widget_infos * infos = new Widget_infos(t,this);
//        mainLayout->addWidget(infos,2,1,1,1);

//        drawerOpened = true;
//    }
//}

//void FirstWindow::closeDrawer()
//{
//    if (drawerOpened)
//    {
//        int size = width();
//        for(int i=0 ; i<15 ; i++)
//        {
//            usleep(10000);
//            size -= 20;
//            setFixedWidth(size);
//        }

//        drawerOpened = false;
//    }
//}
