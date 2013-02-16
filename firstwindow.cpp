#include <unistd.h>
#include <iostream>

#include <QLabel>
#include <QLineEdit>
#include <QTreeWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QMenuBar>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>

#include "firstwindow.h"
#include "widget_infos.h"
#include "widget_ajout.h"
#include "tache.h"
#include "widget_sauvegarde.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent)
{
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

    //Barre des menus
    QMenuBar * bar = new QMenuBar();
    bar->setNativeMenuBar(true);
    bar->addMenu("Fichier");
    bar->addMenu("Affichage");
    setMenuBar(bar);

    // Titre
    QLabel * title = new QLabel("Gestionnaire de tâches");
    title->setAlignment(Qt::AlignCenter);
    QFont titlefont("LMRomanUnsl10");
    title->setFont(titlefont);
    title->setStyleSheet("font-size : 28px");
    mainLayout->addWidget(title,0,0,1,2);

    // Logo
    QLabel * logo = new QLabel();
    QPixmap logoresource("../Toudou/img/toudou.gif");
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
    arbo->setMouseTracking(true);
    arbo->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arbo->setColumnCount(5);

    // signaux - slots de l'arbre
    QObject::connect(arbo,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(popup(QTreeWidgetItem*,int)));
    QObject::connect(arbo,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(tacheChecked(QTreeWidgetItem*,int)));
    QObject::connect(arbo,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(showIcons(QTreeWidgetItem*,int)));
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

    // Bouton Sauvegarder
    QPushButton * savebutton = new QPushButton("Sauvegarder sous...");
    QObject::connect(savebutton,SIGNAL(clicked()),this,SLOT(sauvegarderSous()));

    // Bouton Charger
    QPushButton * loadbutton = new QPushButton("Charger...");
    //QObject::connect(loadbutton,SIGNAL(clicked()),this,SLOT(popupLoad()));

    QHBoxLayout * saveAndLoadLayout = new QHBoxLayout();
    saveAndLoadLayout->addWidget(savebutton);
    saveAndLoadLayout->addWidget(loadbutton);

    pagelayout->addLayout(saveAndLoadLayout);

    // initialisation de la tache racine
    racine = new Tache("Toutes les taches");

    //plusIcon = new QIcon("../Toudou/img/plus.png");


}

FirstWindow::~FirstWindow()
{
}

// popup ajout d une nouvelle tache
void FirstWindow::popup()
{
    currentItem = arbo->invisibleRootItem();
    currentTache = racine;
    Widget_ajout * w_a = new Widget_ajout(this);
    w_a->show();
}

// popup ajout ou delete suivant l'endroit du clic sur la tache dans le QTreeWidgetItem
void FirstWindow::popup(QTreeWidgetItem* i,int n)
{
    if (n == 3 ){
        // Ajout
        currentItem = i;
        defineCurrentTache(i,racine);
        arbo->expandItem(currentItem);
        Widget_ajout * w_a = new Widget_ajout(this);
        w_a->show();
    }
    else if (n == 4){
        // Suppression
        currentItem = i;
        // popup de confirmation
        QMessageBox * supprDiag = new QMessageBox();
        supprDiag->setWindowTitle("Supprimer...");
        supprDiag->addButton("Ok",QMessageBox::AcceptRole);
        supprDiag->addButton("Annuler",QMessageBox::RejectRole);
        supprDiag->setText("La tache " + i->text(0) + " va etre supprimee");
        supprDiag->show();
        // le signal est bien "rejected", c est un bug Qt
        QObject::connect(supprDiag,SIGNAL(rejected()),this,SLOT(deleteItem()));
    }
}

void FirstWindow::deleteItem()
{
    delete(currentItem);
}

void FirstWindow::resetDisable()
{
    this->setDisabled(false);
}

void FirstWindow::tacheChecked(QTreeWidgetItem * item, int n)
{
    if (n==0){
        if (item->checkState(0)==Qt::Checked){
            item->setTextColor(0,QColor(98,188,98));
        }
        else if (item->checkState(0)==Qt::Unchecked){
            item->setTextColor(0,QColor(0,0,0));
        }
    }
}

// les icones + et X apparaissent en "mouseover"
void FirstWindow::showIcons(QTreeWidgetItem *item, int n)
{
    for(int i=0;i<arbo->topLevelItemCount(); ++i){
        QTreeWidgetItem * topchild = arbo->topLevelItem(i);
        eraseIcons(topchild);
    }
    item->setText(3,"[+]");
    item->setText(4,"[X]");
}

// on efface les icones des lignes qui ne sont pas en mouseover
void FirstWindow::eraseIcons(QTreeWidgetItem * item)
{
    item->setText(3,"");
    item->setText(4,"");
    for(int j=0;j<item->childCount(); ++j){
        QTreeWidgetItem * subItem = item->child(j);
        eraseIcons(subItem);
    }

}

// sauvegarder la liste courante sous un nom
void FirstWindow::sauvegarderSous()
{
    widget_sauvegarde * ws = new widget_sauvegarde(this);
    ws->show();
}

void FirstWindow::defineCurrentTache(QTreeWidgetItem *item,Tache * tacheRef)
{
    for(int i=0 ; i<tacheRef->getSousTaches().size() ; i++){
        Tache * t = tacheRef->getSousTaches().at(i);
        if(t->getMatchingItem()==item){
            currentTache = t;
            cout << "nouvelle tache courante definie : " << currentTache->getNom() << endl;
            return;
        }
        else{
            defineCurrentTache(item,t);
        }
    }
}
