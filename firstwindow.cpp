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
    centralwidget->setLayout(mainLayout);

    // Entête fenêtre (title + icon)
    setWindowTitle("Gestionnaire de taches Toudou");

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    bar->setFixedWidth(200);
    QMenu* menuListe = new QMenu("Liste");
    menuListe->addAction("Nouvelle tache");
    menuListe->addSeparator();
    menuListe->addAction("Sauvegarder la liste");
    menuListe->addAction("Charger une liste");
    menuListe->addSeparator();
    menuListe->addAction("Quitter");

    QObject::connect(menuListe,SIGNAL(triggered(QAction*)),this,SLOT(menuAction(QAction*)));

    QMenu* menuAffichage = new QMenu("Affichage");
    QMenu* menuLangue = new QMenu("Langue");
    menuLangue->addAction("Francais");
    menuLangue->addAction("English");
    menuLangue->addAction("Deutsch");
    menuLangue->addAction("Espanol");
    menuAffichage->addMenu(menuLangue);
    menuListe->addSeparator();
    menuAffichage->addAction("Derouler la liste");
    menuAffichage->addAction("Enrouler la liste");

    bar->addMenu(menuListe);
    bar->addMenu(menuAffichage);

    // Titre
    QLabel * title = new QLabel("");
    title->setAlignment(Qt::AlignCenter);
    QFont titlefont("LMRomanUnsl10");
    title->setFont(titlefont);
    title->setStyleSheet("font-size : 28px");
    mainLayout->addWidget(title,0,0,1,2);

    // Logo
    //    QLabel * logo = new QLabel();
    //    QPixmap logoresource("../Toudou/img/toudou.gif");
    //    logo->setPixmap(logoresource);
    //    logo->setAlignment(Qt::AlignCenter);
    //    mainLayout->addWidget(logo,1,0,1,2);

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

    // insertion arbo dans premier onglet
    QWidget * page = new QWidget();
    QVBoxLayout * pagelayout = new QVBoxLayout();
    page->setLayout(pagelayout);
    page->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    pagelayout->addWidget(arbo);
    onglets->addTab(page,"Toutes les tâches");

    // Test second onglet
    //QPushButton * testbutton = new QPushButton("Achevées");
    arboAchevees = new QTreeWidget();
    QHeaderView * headerAchevees = arboAchevees->header();
    headerAchevees->setResizeMode(QHeaderView::ResizeToContents);
    headerAchevees->setResizeMode(0,QHeaderView::Stretch);
    headerAchevees->setStretchLastSection(false);
    arboAchevees->setHeaderHidden(true);
    arboAchevees->setMouseTracking(true);
    arboAchevees->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arboAchevees->setColumnCount(3);

    QWidget * page2 = new QWidget();
    QVBoxLayout * pagelayout2 = new QVBoxLayout();
    page2->setLayout(pagelayout2);
    pagelayout2->addWidget(arboAchevees);
    onglets->addTab(page2,"Achevées");

    // Bouton Nouveau
    QPushButton * newbutton = new QPushButton("Nouveau");
    pagelayout->addWidget(newbutton);
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popup()));

    // Bouton Valider la tache finie
    QPushButton * finishedbutton = new QPushButton("Valider les taches finies");
    QObject::connect(finishedbutton,SIGNAL(clicked()),this,SLOT(confirmFinished()));

    // Bouton Charger // a changer
    QPushButton * loadbutton = new QPushButton("Charger...");
    QObject::connect(loadbutton,SIGNAL(clicked()),this,SLOT(chargerXml()));

    QHBoxLayout * saveAndLoadLayout = new QHBoxLayout();
    saveAndLoadLayout->addWidget(finishedbutton);
    saveAndLoadLayout->addWidget(loadbutton);

    pagelayout->addLayout(saveAndLoadLayout);

    // initialisation de la tache racine
    racine = new Tache("Toutes les taches");
    racine->setMatchingItem(arbo->invisibleRootItem());

}

FirstWindow::~FirstWindow()
{
}

// popup ajout d une nouvelle tache "topLevel"
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
    defineCurrentTache(currentItem,racine);
    currentTache->getTacheParent()->delSousTache(currentTache);
    delete(currentItem);
}

void FirstWindow::resetDisable()
{
    this->setDisabled(false);
}

// change la couleur du texte si la tache est cochee/decochee
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

// retrouve la tache associée à un element de l'arbre
void FirstWindow::defineCurrentTache(QTreeWidgetItem *item,Tache * tacheRef)
{
    for(int i=0 ; i<tacheRef->getSousTaches().size() ; i++){
        Tache * t = tacheRef->getSousTaches().at(i);
        if(t->getMatchingItem()==item){
            currentTache = t;
        }
        else{
            defineCurrentTache(item,t);
        }
    }
}

// chargement de fichier xml en liste : pour l'instant fonctionne mal
void FirstWindow::chargerXml()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Charger une liste"), "",tr("Fichiers Xml (*.xml);"));
    if (fileName != "") {
        // code recopié : il faudra p-e l'utiliser pour plus de securité
        //QFile file(fileName);
        /*if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return;
        }*/
        TiXmlDocument doc(fileName.toStdString());
        doc.LoadFile();
        racine->xmlToTache(doc,arbo);
    }
}

// abandon - plutot implementer la construction de l arbre directement lors du chargement xml
void FirstWindow::tacheToTree(Tache * tacheRef)
{
    for(int i=0 ; tacheRef->getSousTaches().size() ; i++){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(tacheRef->getMatchingItem());
    }
}

// actions selon la partie du menu "Liste" cliqué
void FirstWindow::menuAction(QAction * action)
{
    QString text = action->text();
    if(text=="Nouvelle tache"){
        popup();
    }
    else if(text=="Sauvegarder la liste"){
        sauvegarderSous();
    }
    else if(text=="Charger une liste"){
        chargerXml();
    }
    else if(text=="Quitter"){
        close();
    }
}


// basculer les taches "top level" vers l onglet achevees
void FirstWindow::confirmFinished()
{
    for(int i=0 ; i<arbo->topLevelItemCount() ; i++){
        QTreeWidgetItem * itemCourant = arbo->topLevelItem(i);
        if(itemCourant->checkState(0)==Qt::Checked){
            arboAchevees->addTopLevelItem(itemCourant);
            //delete(itemCourant);
        }
    }
}
