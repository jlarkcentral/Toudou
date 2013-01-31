#include "firstwindow.h"
#include "ui_firstwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QTreeWidget>
#include <unistd.h>
#include <QPushButton>

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FirstWindow)
{
    ui->setupUi(this);
    drawerOpened = false;

    // Taille fenêtre
    setFixedWidth(400);

    // Layout principal (grid)
    QGridLayout * mainLayout = new QGridLayout();
    ui->centralwidget->setLayout(mainLayout);

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
    QTreeWidget * arbo = new QTreeWidget();
    arbo->header()->setVisible(false);
    arbo->setStyleSheet("font-weight : bold; font-size : 18px; ");
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0,"Truc");
    arbo->addTopLevelItem(item);
    QTreeWidgetItem * item2 = new QTreeWidgetItem();
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
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(openDrawer()));
}

FirstWindow::~FirstWindow()
{
    delete ui;
}


void FirstWindow::openDrawer()
{
    if (!drawerOpened)
    {
        int size = width();
        for(int i=0 ; i<15 ; i++)
        {
            usleep(10000);
            size += 25;
            setFixedWidth(size);
        }
        drawerOpened = true;
    }
}

