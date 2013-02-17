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
#include "widget_modif.h"

FirstWindow::FirstWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Taille fenêtre
    setMinimumWidth(500);

    // Layout principal (grid)
    QWidget * centralwidget = new QWidget(this);
    setCentralWidget(centralwidget);
    mainLayout = new QGridLayout();
    centralwidget->setLayout(mainLayout);

    // Entête fenêtre (title + icon)
    setWindowTitle("Gestionnaire de taches Toudou");
    setWindowIcon(QIcon("../Toudou/img/toudouIcon.gif"));

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    bar->setFixedWidth(200);
    QMenu* menuListe = new QMenu("Liste");
    menuListe->addAction("Nouvelle tache");
    menuListe->addSeparator();
    menuListe->addAction("Valider les taches finies");
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
    menuLangue->setDisabled(true);
    menuListe->addSeparator();
    menuAffichage->addAction("Developper la liste");
    menuAffichage->addAction("Reduire la liste");

    QObject::connect(menuAffichage,SIGNAL(triggered(QAction*)),this,SLOT(menuAction(QAction*)));

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

    // menu contextuel de l'arbre
    contextMenu = new QMenu(arbo);
    QAction * modifAction = new QAction("Modifier...",contextMenu);
    QAction * templateAction = new QAction("Créer un type de tache...",contextMenu);
    contextMenu->addAction(modifAction);
    contextMenu->addSeparator();
    contextMenu->addAction(templateAction);
    arbo->addAction(modifAction);
    arbo->addAction(templateAction);

    QObject::connect(contextMenu,SIGNAL(triggered(QAction*)),this,SLOT(contextMenuAction(QAction*)));


    // signaux - slots de l'arbre
    QObject::connect(arbo,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(popup(QTreeWidgetItem*,int)));
    QObject::connect(arbo,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(tacheChecked(QTreeWidgetItem*,int)));
    QObject::connect(arbo,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(showIcons(QTreeWidgetItem*,int)));


    //QObject::connect(arbo,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(contextMenu(QPoint)));

    // insertion arbo dans premier onglet
    QWidget * page = new QWidget();
    QVBoxLayout * pagelayout = new QVBoxLayout();
    page->setLayout(pagelayout);
    page->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    pagelayout->addWidget(arbo);
    onglets->addTab(page,"Tâches en cours");

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
    onglets->addTab(page2,"Taches finies");

    // Bouton Nouveau
    QPushButton * newbutton = new QPushButton("Nouvelle tache");
    pagelayout->addWidget(newbutton);
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popup()));

    // Bouton Valider la tache finie
    finishedbutton = new QPushButton("Valider les taches finies");
    finishedbutton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(finishedbutton,SIGNAL(clicked()),this,SLOT(confirmFinished()));

    // Bouton Develloper/Reduire
    expand = true;
    displaybutton = new QPushButton("Developper/Reduire");
    displaybutton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(displaybutton,SIGNAL(clicked()),this,SLOT(developOrReduce()));

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(finishedbutton);
    buttonsLayout->addWidget(displaybutton);

    pagelayout->addLayout(buttonsLayout);

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
        supprDiag->addButton("Ok",QMessageBox::RejectRole);
        supprDiag->addButton("Annuler",QMessageBox::AcceptRole);
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
            //if(areSubItemsChecked(item)){
            item->setTextColor(0,QColor(98,188,98));
            //}
            //else item->setCheckState(0,Qt::Unchecked); // pas forcement pertinent

        }
        else if (item->checkState(0)==Qt::Unchecked){
            item->setTextColor(0,QColor(0,0,0));
        }
    }
}

bool FirstWindow::areSubItemsChecked(QTreeWidgetItem *item)
{
    for(int i=0 ; i<item->childCount() ; i++){
        if(item->child(i)->checkState(0)==Qt::Unchecked){
            return false;
        }
    }
    return true;
}

// les icones + et X apparaissent en "mouseover"
void FirstWindow::showIcons(QTreeWidgetItem *item, int n)
{
    for(int i=0;i<arbo->topLevelItemCount(); ++i){
        QTreeWidgetItem * topchild = arbo->topLevelItem(i);
        eraseIcons(topchild);
    }
    //item->setText(3,"[+]");
    //item->setText(4,"[X]");
    item->setIcon(3,QIcon("../Toudou/img/pluslarge.png"));
    item->setIcon(4,QIcon("../Toudou/img/deletelarge.png"));

    arbo->setContextMenuPolicy(Qt::ActionsContextMenu);
}

// on efface les icones des lignes qui ne sont pas en mouseover
void FirstWindow::eraseIcons(QTreeWidgetItem * item)
{
    //item->setText(3,"");
    //item->setText(4,"");
    item->setIcon(3,QIcon());
    item->setIcon(4,QIcon());
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
        TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
        xmlToTache(element,arbo->invisibleRootItem(),racine);
        currentItem = arbo->invisibleRootItem();
    }
}

// ancienne fonction de Tache : xml vers une structure de Tache, ajout dans l'arbre
void FirstWindow::xmlToTache(TiXmlElement * element,QTreeWidgetItem *item,Tache * tache)
{
    while(element){
        Tache * newTache = new Tache(element->Attribute("nom"));
        tache->addSousTache(newTache);
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        item->addChild(newItem);
        item->setCheckState(0,Qt::Unchecked);
        newTache->setMatchingItem(newItem);
        newItem->setText(0,QString(newTache->getNom().c_str()));
        newItem->setCheckState(0,Qt::Unchecked);

        xmlToTache(element->FirstChildElement(),newItem,newTache);

        element = element->NextSiblingElement();
    }
}

// actions selon la partie du menu "Liste" cliqué
void FirstWindow::menuAction(QAction * action)
{
    QString text = action->text();
    if(text=="Nouvelle tache"){
        popup();
    }
    if(text=="Valider les taches finies"){
        confirmFinished();
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
    else if(text=="Developper la liste"){
        developOrReduce();
    }
    else if(text=="Reduire la liste"){
        developOrReduce();
    }
}


//basculer les taches "top level" vers l onglet achevees
void FirstWindow::confirmFinished()
{
    for(int i=0 ; i<arbo->topLevelItemCount() ; i++){
        QTreeWidgetItem * itemCourant = arbo->topLevelItem(i);
        if(itemCourant->checkState(0)==Qt::Checked){
            QTreeWidgetItem * toAdd = itemCourant->clone();
            toAdd->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );

            confirmFinishedSubItems(toAdd);

            arboAchevees->addTopLevelItem(toAdd);
            delete(itemCourant);
            i--;
        }
    }
}

void FirstWindow::confirmFinishedSubItems(QTreeWidgetItem * item)
{
    for(int j=0 ; j<item->childCount() ; j++){
        QTreeWidgetItem * subItemCourant = item->child(j);
        subItemCourant->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
        confirmFinishedSubItems(subItemCourant);
    }
}

// developpe ou reduit l'arbre entier depuis le meme bouton
void FirstWindow::developOrReduce()
{
    for(int i=0 ; i<arbo->topLevelItemCount() ; i++){
        QTreeWidgetItem * itemCourant = arbo->topLevelItem(i);
        itemCourant->setExpanded(!expand);
        developOrReduceRecursion(itemCourant);
    }
    expand = !expand;
}

void FirstWindow::developOrReduceRecursion(QTreeWidgetItem *item)
{
    for(int j=0 ; j<item->childCount() ; j++){
        QTreeWidgetItem * subItemCourant = item->child(j);
        subItemCourant->setExpanded(!expand);
        developOrReduceRecursion(subItemCourant);
    }
}

void FirstWindow::enableButtons()
{
    finishedbutton->setEnabled(true);
    displaybutton->setEnabled(true);
}

void FirstWindow::contextMenuAction(QAction *action)
{
    QString text = action->text();
    if(text=="Modifier..."){
        if (arbo->selectedItems().size()>0){
            currentItem = arbo->selectedItems().at(0);
            if (currentItem->checkState(0)==Qt::Unchecked){
                Widget_modif * modif = new Widget_modif(currentItem,this,0);
                modif->show();
            }
        }
    }
    else if (text=="Créer un type de tache..."){
        // devra etre un widget_template dans une implementation fonctionnelle
        widget_sauvegarde *ws = new widget_sauvegarde(this);
        ws->show();
    }
}
