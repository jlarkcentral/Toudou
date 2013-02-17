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
#include "widget_template.h"

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
    menuListe->addAction("Charger un type de tache");
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
    menuAffichage->addSeparator();
    menuAffichage->addAction("Developper la liste");
    menuAffichage->addAction("Reduire la liste");
    menuAffichage->addSeparator();
    QAction * affAide = new QAction("Afficher les bulles d'aide",0);
    affAide->setCheckable(true);
    affAide->setChecked(true);
    menuAffichage->addAction(affAide);

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
    header->setResizeMode(2,QHeaderView::Fixed);
    header->setResizeMode(3,QHeaderView::Fixed);
    header->setStretchLastSection(false);
    arbo->setHeaderHidden(true);
    arbo->setMouseTracking(true);
    arbo->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arbo->setColumnCount(4);
    arbo->setSelectionMode(QAbstractItemView::NoSelection);

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

    // insertion arbo dans premier onglet
    QWidget * page = new QWidget();
    QVBoxLayout * pagelayout = new QVBoxLayout();
    page->setLayout(pagelayout);
    page->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    pagelayout->addWidget(arbo);
    onglets->addTab(page,"Tâches en cours");

    // Test second onglet
    arboAchevees = new QTreeWidget();
    QHeaderView * headerAchevees = arboAchevees->header();
    headerAchevees->setResizeMode(QHeaderView::ResizeToContents);
    headerAchevees->setResizeMode(0,QHeaderView::Stretch);
    headerAchevees->setStretchLastSection(false);
    arboAchevees->setHeaderHidden(true);
    arboAchevees->setMouseTracking(true);
    arboAchevees->setStyleSheet("font-weight : bold; font-size : 18px; ");
    arboAchevees->setColumnCount(2);
    arboAchevees->setSelectionMode(QAbstractItemView::NoSelection);

    QObject::connect(arboAchevees,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(showLineTabFinished(QTreeWidgetItem*,int)));

    QWidget * page2 = new QWidget();
    QVBoxLayout * pagelayout2 = new QVBoxLayout();
    page2->setLayout(pagelayout2);
    pagelayout2->addWidget(arboAchevees);
    onglets->addTab(page2,"Taches finies");

    // Bouton Nouveau
    newbutton = new QPushButton("Nouvelle tache");
    newbutton->setStyleSheet("QPushButton {background : #3A9D23 ; color : #FFFFFF ; font-weight : bold; font-size : 18px;}");
    pagelayout->addWidget(newbutton);
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popup()));
    newbutton->setToolTip("Ajouter une nouvelle tache à la liste");

    // Bouton Valider la tache finie
    finishedbutton = new QPushButton("Valider les taches finies");
    finishedbutton->setStyleSheet("QPushButton {font-size : 18px;}");
    finishedbutton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(finishedbutton,SIGNAL(clicked()),this,SLOT(confirmFinished()));
    finishedbutton->setToolTip("Basculer toutes les taches achevées vers l'onglet \"Taches finies\"");

    // Bouton Develloper/Reduire
    expand = true;
    displaybutton = new QPushButton("Reduire la liste");
    displaybutton->setStyleSheet("QPushButton {font-size : 18px;}");
    displaybutton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(displaybutton,SIGNAL(clicked()),this,SLOT(developOrReduce()));
    displaybutton->setToolTip("Cacher les étapes des taches");

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(finishedbutton);
    buttonsLayout->addWidget(displaybutton);

    pagelayout->addLayout(buttonsLayout);

    // initialisation de la tache racine
    racine = new Tache("Toutes les taches");
    racine->setMatchingItem(arbo->invisibleRootItem());

    // ouvrir le backup
    QFile file("../Toudou/xml/backup.xml");
    if (file.open(QIODevice::ReadOnly)) {
        chargerXml("../Toudou/xml/backup.xml");
    }
    arbo->expandAll();

    // ouvrir les taches finies
    QFile fileFinished("../Toudou/xml/saveFinished.xml");
    if (fileFinished.open(QIODevice::ReadOnly)) {
        chargerXmlFinished("../Toudou/xml/saveFinished.xml");
    }
    arboAchevees->expandAll();

    // sauvegarder pour prochaine session
    QObject::connect(this,SIGNAL(appClosed()),this,SLOT(sauvegarderSession()));
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
    if (n == 2 ){
        // Ajout
        currentItem = i;
        defineCurrentTache(i,racine);
        arbo->expandItem(currentItem);
        Widget_ajout * w_a = new Widget_ajout(this);
        w_a->show();
    }
    else if (n == 3){
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
            item->setTextColor(0,QColor(58,157,35));
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
    item->setIcon(2,QIcon("../Toudou/img/pluslarge.png"));
    item->setIcon(3,QIcon("../Toudou/img/deletelarge.png"));
    item->setToolTip(2,"Ajouter une étape à cette tache");
    item->setToolTip(3,"Supprimer cette tache");
    for(int r=0 ; r<4 ; r++){
        item->setBackgroundColor(r,QColor(230,230,230));
    }
    arbo->setContextMenuPolicy(Qt::ActionsContextMenu);
}

// la ligne de surbrillance apparait dans l'onglet Taches finies
void FirstWindow::showLineTabFinished(QTreeWidgetItem *item, int n)
{
    for(int i=0;i<arboAchevees->topLevelItemCount(); ++i){
        QTreeWidgetItem * topchild = arboAchevees->topLevelItem(i);
        eraseIcons(topchild);
    }
    for(int r=0 ; r<4 ; r++){
        item->setBackgroundColor(r,QColor(230,230,230));
    }
}

// on efface les icones des lignes qui ne sont pas en mouseover
void FirstWindow::eraseIcons(QTreeWidgetItem * item)
{
    item->setIcon(2,QIcon());
    item->setIcon(3,QIcon());
    for(int r=0 ; r<4 ; r++){
        item->setBackgroundColor(r,QColor(255,255,255));
    }
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

void FirstWindow::creerTemplateSous()
{
    defineCurrentTache(arbo->currentItem(),racine);
    if(currentTache->getTacheParent()){
        widget_template * wt = new widget_template(currentTache->getTacheParent(),this,0);
        wt->show();
        currentTache = racine;
    }
}

void FirstWindow::sauvegarderSession()
{
    racine->createXml("backup");
    createXmlforTree("saveFinished");
}


// retrouve la tache associée à un element de l'arbre
void FirstWindow::defineCurrentTache(QTreeWidgetItem *item,Tache * tacheRef)
{
    for(uint i=0 ; i<tacheRef->getSousTaches().size() ; i++){
        Tache * t = tacheRef->getSousTaches().at(i);
        if(t->getMatchingItem()==item){
            currentTache = t;
        }
        else{
            defineCurrentTache(item,t);
        }
    }
}

// chargement de fichier xml en liste
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
        TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
        if(element){
            xmlToTache(element,arbo->invisibleRootItem(),racine);
        }
        currentItem = arbo->invisibleRootItem();
    }
}

// chargement de type de tache : fichier xml en liste avec 1er noeud
void FirstWindow::chargerXmlTemplate()
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
        if(element){
            xmlToTache(element,arbo->invisibleRootItem(),racine);
        }
        currentItem = arbo->invisibleRootItem();
    }
}

void FirstWindow::chargerXml(string fileName)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();
    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTache(element,arbo->invisibleRootItem(),racine);
    }
    currentItem = arbo->invisibleRootItem();
}

// ancienne fonction de Tache : xml vers une structure de Tache, ajout dans l'arbre
void FirstWindow::xmlToTache(TiXmlElement * element,QTreeWidgetItem *item,Tache * tache)
{
    while(element){
        Tache * newTache = new Tache(element->Attribute("nom"));
        if(element->Attribute("dateAbs")){
            QDate * qdt;
            newTache->setDateabs(qdt->fromString(element->Attribute("dateAbs")));
            newTache->setDate(1);
        }
        else if(element->Attribute("dateRel")){
            newTache->setDaterel(element->Attribute("dateRel"));
            newTache->setDate(2);
        }
        else newTache->setDate(3);

        tache->addSousTache(newTache);
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        item->addChild(newItem);
        item->setCheckState(0,Qt::Unchecked);
        newTache->setMatchingItem(newItem);
        newItem->setText(0,QString(newTache->getNom().c_str()));
        if(newTache->getDate()==1){
            newItem->setText(1,QString(newTache->getDateabs().toString()));
            newItem->setTextColor(1,QColor(152,152,152));
        }
        else if(newTache->getDate()==2){
            newItem->setText(1,QString(newTache->getDaterel().c_str()));
            newItem->setTextColor(1,QColor(152,152,152));
        }

        newItem->setCheckState(0,Qt::Unchecked);

        xmlToTache(element->FirstChildElement(),newItem,newTache);

        element = element->NextSiblingElement();
    }
}


void FirstWindow::chargerXmlFinished(string fileName)
{
    TiXmlDocument doc(fileName);
    doc.LoadFile();
    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTacheFinished(element,arboAchevees->invisibleRootItem());
    }
    currentItem = arbo->invisibleRootItem();
}

// ancienne fonction de Tache : xml vers une structure de Tache, ajout dans l'arbre
void FirstWindow::xmlToTacheFinished(TiXmlElement * element,QTreeWidgetItem *item)
{
    while(element){
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        item->addChild(newItem);
        newItem->setText(0,QString(element->Attribute("nom")));
        newItem->setTextColor(0,QColor(58,157,35));
        newItem->setText(1,QString(element->Attribute("date")));
        newItem->setTextColor(1,QColor(152,152,152));

        xmlToTacheFinished(element->FirstChildElement(),newItem);

        element = element->NextSiblingElement();
    }
}

// actions selon la partie du menu cliqué
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
    else if(text=="Charger un type de tache"){
        chargerXmlTemplate();
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
    else if(text=="Afficher les bulles d'aide"){
        if(!action->isChecked()){
            newbutton->setToolTip("");
            finishedbutton->setToolTip("");
            displaybutton->setToolTip("");
            action->setChecked(false);
        }
        else{
            newbutton->setToolTip("Ajouter une nouvelle tache à la liste");
            finishedbutton->setToolTip("Basculer toutes les taches achevées vers l'onglet \"Taches finies\"");
            displaybutton->setToolTip("Cacher les étapes des taches");
            action->setChecked(true);
        }
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
            defineCurrentTache(itemCourant,racine);
            Tache * currentTacheParent = currentTache->getTacheParent();
            currentTacheParent->delSousTache(currentTache);
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
    if(expand){
        displaybutton->setText("Développer la liste");
        displaybutton->setToolTip("Faire apparaitre toutes les étapes des taches");
    }
    else{
        displaybutton->setText("Réduire la liste");
        displaybutton->setToolTip("Cacher les étapes des taches");
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
    QTreeWidgetItem * item = arbo->currentItem();
    QString text = action->text();
    if(text=="Modifier..."){
        if (item){
            currentItem = item;
            if (currentItem->checkState(0)==Qt::Unchecked){
                Widget_modif * modif = new Widget_modif(currentItem,this,0);
                modif->show();
            }
        }
    }
    else if (text=="Créer un type de tache..."){
        if(item){
            defineCurrentTache(item,racine);
            widget_template * wt = new widget_template(currentTache,this,0);
            wt->show();
            currentTache = racine;
        }
    }
}

void FirstWindow::closeEvent(QCloseEvent *event)
{
    emit appClosed();
    event->accept();
}

// initialiser le fichier xml
void FirstWindow::createXmlforTree(string nomFichier)
{
    TiXmlDocument doc("../Toudou/xml/"+nomFichier+".xml");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );
    TiXmlElement * firstElement = new TiXmlElement( "racine" );
    doc.LinkEndChild( firstElement );

    addItemInXml(doc,firstElement,arboAchevees->invisibleRootItem());

    doc.SaveFile();

}

// remplir le fichier xml avec l'arbre
void FirstWindow::addItemInXml(TiXmlDocument doc,TiXmlElement * element,QTreeWidgetItem * item)
{
    TiXmlElement * newElement = new TiXmlElement("tache");
    newElement->SetAttribute("nom",item->text(0).toStdString());
    newElement->SetAttribute("date",item->text(1).toStdString());
    // TODO : modif avec les nouvelles dates
    // newElement->SetAttribute("date",date.toString().toStdString());
    element->LinkEndChild( newElement );

    for (int i=0 ; i<item->childCount() ; i++){
        QTreeWidgetItem * subItem = item->child(i);
        addItemInXml(doc,newElement,subItem);
    }
}
