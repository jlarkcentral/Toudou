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
    drawerOpened = false;

    // Taille fenêtre
    setFixedWidth(420);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
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
    onglets->setFixedWidth(400);
    mainLayout->addWidget(onglets,2,0,1,1);

    // TreeWidget
    //QTreeWidget * arbo = new QTreeWidget();
    arbo = new QTreeWidget();
    QHeaderView * header = arbo->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    arbo->setHeaderHidden(true);
    arbo->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arbo->setColumnCount(2);

    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setCheckState(0,Qt::Unchecked);
    item->setText(0,"Truc");
    // Test insertion bouton
    QPushButton * plus = new QPushButton();
    plus->setStyleSheet("background-image : url(img/plus.png); background-repeat : no-repeat");
    plus->setAutoFillBackground(true);
    plus->setFixedWidth(34);
    item->setFlags(item->flags() | (Qt::ItemIsEditable));
    arbo->addTopLevelItem(item);
    arbo->setItemWidget(item,1,plus); // ATTENTION : à faire après avoir placé l'item dans l'arbre, sinon marche pas

    // Test
    QObject::connect(arbo,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(popAjout(QTreeWidgetItem*,int)));

    /*QTreeWidgetItem * item2 = new QTreeWidgetItem();
    item2->setText(0,"Troussepinette");
    arbo->addTopLevelItem(item2);
    QTreeWidgetItem * item3 = new QTreeWidgetItem();
    item3->setText(0,"Prout");
    arbo->addTopLevelItem(item3);
    QTreeWidgetItem * item4 = new QTreeWidgetItem(item3);
    item4->setText(0,"Fourchette");
    arbo->addTopLevelItem(item4);
    QTreeWidgetItem * item5 = new QTreeWidgetItem(item3);
    item5->setText(0,"Couteau");
    arbo->addTopLevelItem(item5);
*/
    // insertion arbo dans premier onglet
    QWidget * page = new QWidget();
    QVBoxLayout * pagelayout = new QVBoxLayout();
    page->setLayout(pagelayout);
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
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popAjout()));

}

FirstWindow::~FirstWindow()
{
}

// popup ajout d une nouvelle tache
void FirstWindow::popAjout()
{
    Widget_ajout * w_a = new Widget_ajout(this);
    w_a->show();
}


void FirstWindow::popAjout(QTreeWidgetItem* i, int column)
{
    if (column == 1)
    {
        Widget_ajout * w_a = new Widget_ajout(this);
        w_a->show();
    }
}


void FirstWindow::openDrawer()
{
    if (!drawerOpened)
    {
        int size = width();
        for(int i=0 ; i<15 ; i++)
        {
            usleep(10000);
            size += 20;
            setFixedWidth(size);
        }

        // TEST : tâche
        Tache * t = new Tache("Ma jolie tâche");
        t->setDate("7 février 2013");
        t->setFini(false);

        Widget_infos * infos = new Widget_infos(t,this);
        mainLayout->addWidget(infos,2,1,1,1);

        drawerOpened = true;
    }
}

void FirstWindow::closeDrawer()
{
    if (drawerOpened)
    {
        int size = width();
        for(int i=0 ; i<15 ; i++)
        {
            usleep(10000);
            size -= 20;
            setFixedWidth(size);
        }

        drawerOpened = false;
    }
}
