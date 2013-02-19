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
#include <QStatusBar>

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

    statbar = new QStatusBar(this);
    setStatusBar(statbar);

    // Entête fenêtre (title + icon)
    //setWindowTitle("Gestionnaire de taches Toudou");
    setWindowIcon(QIcon("../Toudou/img/toudouIcon.gif"));

    //Barre des menus
    QMenuBar * bar = new QMenuBar(this);
    bar->setFixedWidth(200);
    QMenu* menuListe = new QMenu("&Liste");
    QAction * nouvelletache = new QAction("Nouvelle tâche",menuListe);
    nouvelletache->setShortcut(Qt::Key_Space);
    menuListe->addAction(nouvelletache);
    menuListe->addSeparator();
    QAction * validerfinies = new QAction("Valider les tâches finies",menuListe);
    validerfinies->setShortcut(QKeySequence("Ctrl+V"));
    validerfinies->setIcon(QIcon("../Toudou/img/checkbox-checked-th.png"));
    menuListe->addAction(validerfinies);
    QAction * sauverliste = new QAction("Sauvegarder la liste",menuListe);
    sauverliste->setShortcut(QKeySequence("Ctrl+S"));
    menuListe->addAction(sauverliste);
    QAction * chargerliste = new QAction("Charger une liste",menuListe);
    chargerliste->setShortcut(QKeySequence("Ctrl+O"));
    menuListe->addAction(chargerliste);
    /*QAction * chargertemplate = new QAction("Charger un type de tâche",menuListe);
    chargertemplate->setShortcut(QKeySequence("Ctrl+T"));
    menuListe->addAction(chargertemplate);*/
    QAction * supprliste = new QAction("Supprimer la liste",menuListe);
    supprliste->setShortcut(Qt::Key_Delete);
    menuListe->addAction(supprliste);
    menuListe->addSeparator();
    QAction * quitter = new QAction("Quitter",menuListe);
    quitter->setShortcut(QKeySequence("Ctrl+Q"));
    menuListe->addAction(quitter);

    QObject::connect(menuListe,SIGNAL(triggered(QAction*)),this,SLOT(menuAction(QAction*)));

    QMenu* menuAffichage = new QMenu("&Affichage");
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

    QObject::connect(menuAffichage,SIGNAL(triggered(QAction*)),this,SLOT(menuAction(QAction*)));

    bar->addMenu(menuListe);
    bar->addMenu(menuAffichage);

    // Titre

    QLabel * title = new QLabel(""); //("Gestionnaire de tâches");
    title->setAlignment(Qt::AlignCenter);
    //QFont titlefont("LMRomanUnsl10");
    //title->setFont(titlefont);
    title->setStyleSheet("font-size : 16px");
    mainLayout->addWidget(title,0,0,1,2);

    // Onglets
    QTabWidget * onglets = new QTabWidget();
    onglets->setStyleSheet("QTabWidget{font-size : 16px}");
    //onglets->setFont(titlefont);
    //onglets->setFixedWidth(400);
    mainLayout->addWidget(onglets,2,0,1,1);

    // TreeWidget
    arbo = new QTreeWidget();
    currentItem = arbo->invisibleRootItem();
    QHeaderView * header = arbo->header();
    header->setResizeMode(QHeaderView::ResizeToContents);
    header->setResizeMode(0,QHeaderView::Stretch);
    header->setResizeMode(2,QHeaderView::Fixed);
    header->setResizeMode(3,QHeaderView::ResizeToContents);
    header->setStretchLastSection(false);
    arbo->setHeaderHidden(true);
    arbo->setMouseTracking(true);
    arbo->setStyleSheet("font-size : 18px; ");
    arbo->setColumnCount(4);
    arbo->setSelectionMode(QAbstractItemView::NoSelection);

    // menu contextuel de l'arbre
    contextMenu = new QMenu(arbo);
    QAction * modifAction = new QAction("Modifier...",contextMenu);
    QAction * templateAction = new QAction("Créer un type de tâche...",contextMenu);
    QAction * addAction = new QAction("Ajouter une étape",contextMenu);
    addAction->setIcon(QIcon("../Toudou/img/pluslarge.png"));
    QAction * deleteAction = new QAction("Supprimer",contextMenu);
    contextMenu->addAction(addAction);
    contextMenu->addSeparator();
    contextMenu->addAction(modifAction);
    contextMenu->addSeparator();
    contextMenu->addAction(templateAction);
    contextMenu->addAction(modifAction);
    contextMenu->addSeparator();
    arbo->addAction(addAction);
    arbo->addAction(modifAction);
    arbo->addAction(templateAction);
    arbo->addAction(deleteAction);

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
    arboAchevees->setStyleSheet("font-size : 18px; ");
    arboAchevees->setColumnCount(2);
    arboAchevees->setSelectionMode(QAbstractItemView::NoSelection);

    QObject::connect(arboAchevees,SIGNAL(itemEntered(QTreeWidgetItem*,int)),this,SLOT(showLineTabFinished(QTreeWidgetItem*,int)));

    QWidget * page2 = new QWidget();
    QVBoxLayout * pagelayout2 = new QVBoxLayout();
    page2->setLayout(pagelayout2);
    pagelayout2->addWidget(arboAchevees);
    onglets->addTab(page2,"Tâches finies");
    QPushButton * viderListe = new QPushButton("Vider la liste des tâches finies");
    pagelayout2->addWidget(viderListe);
    viderListe->setStyleSheet("QPushButton {font-size : 18px;}");
    QObject::connect(viderListe,SIGNAL(clicked()),this,SLOT(deleteFinished()));

    // Bouton Nouveau
    newbutton = new QPushButton("Nouvelle tâche");
    newbutton->setStyleSheet("QPushButton {color : #3A9D23 ; font-weight : bold; font-size : 22px;}");
    newbutton->setFixedHeight(50);
    newbutton->setIcon(QIcon("../Toudou/img/pluslarge.png"));
    pagelayout->addWidget(newbutton);
    QObject::connect(newbutton,SIGNAL(clicked()),this,SLOT(popup()));
    newbutton->setToolTip("Ajouter une nouvelle tâche à la liste");

    // Bouton Valider la tache finie
    finishedbutton = new QPushButton("Valider les tâches finies");
    finishedbutton->setStyleSheet("QPushButton {font-size : 18px;}");
    finishedbutton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(finishedbutton,SIGNAL(clicked()),this,SLOT(confirmFinished()));
    finishedbutton->setToolTip("Basculer toutes les tâches achevées vers l'onglet \"Tâches finies\"");
    finishedbutton->setIcon(QIcon("../Toudou/img/checkbox-checked-th.png"));

    // Bouton Sauvegarder
    expand = true;
    saveButton = new QPushButton("Sauvegarder la liste");
    saveButton->setStyleSheet("QPushButton {font-size : 18px;}");
    saveButton->setEnabled(true); // changer avec l'ajout...
    QObject::connect(saveButton,SIGNAL(clicked()),this,SLOT(sauvegarderSous()));
    saveButton->setToolTip("Sauvegarder cette liste sous un nom");
    saveButton->setIcon(QIcon("../Toudou/img/document_save.png"));

    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(finishedbutton);
    buttonsLayout->addWidget(saveButton);

    pagelayout->addLayout(buttonsLayout);

    // initialisation de la tache racine
    racine = new Tache("Toutes les tâches");
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

    // verifier si il y a des taches pour ce jour
    todoToday();

    // chargement des templates
    templates = new Tache("templates");
    templatesTree = new QTreeWidget();
    QFile fileTemplates("../Toudou/xml/templates.xml");
    if (fileTemplates.open(QIODevice::ReadOnly)) {
        chargerXml("../Toudou/xml/templates.xml",templatesTree->invisibleRootItem(),templates);
    }



    // sauvegarder pour prochaine session
    QObject::connect(this,SIGNAL(appClosed()),this,SLOT(sauvegarderSession()));
}

FirstWindow::~FirstWindow()
{
}

// Enlever les checkboxes des sous-taches d'un item
void FirstWindow::removeCheckboxes(QTreeWidgetItem *item)
{
    item->setData(0, Qt::CheckStateRole, QVariant());
    for (int i = 0; i < item->childCount(); i++)
    {
        removeCheckboxes(item->child(i));
    }
}

// Disable les sous-taches d'un template
void FirstWindow::disableSubtasks(QTreeWidgetItem *item)
{
    //item->setDisabled(true);
    for (int i = 0; i < item->childCount(); i++)
    {
        item->child(i)->setDisabled(true);
        item->child(i)->setTextColor(0,QColor(152,152,152));
        disableSubtasks(item->child(i));
    }
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
        supprDiag->addButton("Annuler",QMessageBox::RejectRole);
        supprDiag->addButton("Ok",QMessageBox::AcceptRole);

        supprDiag->setText("La tâche " + i->text(0) + " va etre supprimee");
        supprDiag->show();
        // le signal est bien "rejected", c est un bug Qt
        QObject::connect(supprDiag,SIGNAL(accepted()),this,SLOT(deleteItem()));
    }
}

void FirstWindow::deleteItem()
{
    defineCurrentTache(currentItem,racine);
    currentTache->getTacheParent()->delSousTache(currentTache);
    bool ordre = currentTache->getTacheParent()->getOrdon();
    delete(currentItem);
    if (ordre)
    {
        QTreeWidgetItem * parent = currentItem->parent();
        QString oldname;
        QString newname;
        ostringstream number;
        string numberString;
        for (int i = 0; i < parent->childCount(); i++)
        {
            oldname = parent->child(i)->text(0);
            newname = oldname.remove(0,1);
            number << i+1;
            numberString = number.str();
            newname = QString(numberString.c_str()) + newname;
            parent->child(i)->setText(0,newname);
            number.str("");
        }
    }
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
            //            defineCurrentTache(item,racine);
            //            Tache * ct = currentTache;
            bool subitemscheck = true;
            //            for(int i=0 ; ct->getSousTaches().size() ; i++){
            //                Tache * cti = ct->getSousTaches().at(i);
            //                if(!cti->getFini()){
            //                    precondConflit = true;
            //                }
            //            }
            subitemscheck = areSubItemsChecked(item);
            if(!subitemscheck){
                statbar->showMessage("La tache " +item->text(0)+ " ne respecte pas les preconditions !");
            }
            else statbar->showMessage("");
            item->setTextColor(0,QColor(58,157,35));
            defineCurrentTache(item,racine);
            currentTache->setFini(true);
            currentTache = racine;

        }
        else if (item->checkState(0)==Qt::Unchecked){
            item->setTextColor(0,QColor(0,0,0));
            defineCurrentTache(item,racine);
            currentTache->setFini(false);
            currentTache = racine;
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
    item->setToolTip(2,"Ajouter une étape à cette tâche");
    item->setToolTip(3,"Supprimer cette tâche");
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

void FirstWindow::sauvegarderTemplates()
{
    templates->createXml("templates");
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
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Charger une liste"), "",tr("Fichiers Xml (*.xml);"));
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Charger une liste",
                                                    "../Toudou/xml",
                                                    "Fichiers xml (*.xml)",new QString(),
                                                    QFileDialog::DontUseNativeDialog);
    if (fileName != "") {
        // code recopié : il faudra p-e l'utiliser pour plus de securité
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return;
        }
    }

    string fileNameString = fileName.toStdString();

    const char * charfilename = fileNameString.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();
    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTache(element,arbo->invisibleRootItem(),racine);
    }
    currentItem = arbo->invisibleRootItem();

}

// chargement de type de tache : fichier xml en liste avec 1er noeud
void FirstWindow::chargerXmlTemplate()
{
    QString fileName = QFileDialog::getOpenFileName(this,
<<<<<<< HEAD
                                                   "Charger un type de tâche",
                                                   "../Toudou/xml",
                                                   "Fichiers xml (*.xml)",new QString(),
                                                   QFileDialog::DontUseNativeDialog);
=======
                                                    "Charger un type de tache",
                                                    "../Toudou/xml",
                                                    "Fichiers xml (*.xml)",new QString(),
                                                    QFileDialog::DontUseNativeDialog);
>>>>>>> b52894cb0c2f87bf5b94494267f2746c84c78fa1
    if (fileName != "") {
        // code recopié : il faudra p-e l'utiliser pour plus de securité
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"),
                                  tr("Could not open file"));
            return;
        }
    }


    string fileNameString = fileName.toStdString();
    const char * charfilename = fileNameString.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();
    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTache(element,arbo->invisibleRootItem(),racine);
    }
    currentItem = arbo->invisibleRootItem();

}

void FirstWindow::chargerXml(string fileName)
{
    const char * charfilename = fileName.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTache(element,arbo->invisibleRootItem(),racine);
    }
    currentItem = arbo->invisibleRootItem();
}

void FirstWindow::chargerXml(string fileName,QTreeWidgetItem * item,Tache * tacheRacine)
{
    const char * charfilename = fileName.c_str();
    TiXmlDocument doc(charfilename);
    doc.LoadFile();

    TiXmlElement * element = doc.FirstChildElement()->FirstChildElement()->FirstChildElement();
    if(element){
        xmlToTache(element,item,tacheRacine);
    }
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

        bool checked = false;
        if(element->Attribute("checked")){
            string attributChecked = element->Attribute("checked");
            if (attributChecked=="1"){
                checked = true;
            }
        }
        newTache->setFini(checked);

        bool ordonnee = false;
        if(element->Attribute("ordonnee")){
            string attributOrdonnee = element->Attribute("ordonnee");
            if (attributOrdonnee=="1"){
                ordonnee = true;
            }
        }
        newTache->setOrdon(ordonnee);

        tache->addSousTache(newTache);
        QTreeWidgetItem * newItem = new QTreeWidgetItem(item);
        item->addChild(newItem);
        newTache->setMatchingItem(newItem);

        if(tache->getOrdon()){
            ostringstream number;
            number << tache->getSousTaches().size();
            string numberString = number.str();

            newItem->setText(0,QString(numberString.c_str())+". "+QString(newTache->getNom().c_str()));
        }
        else newItem->setText(0,QString(newTache->getNom().c_str()));

        if(newTache->getDate()==1){
            newItem->setText(1,QString(newTache->getDateabs().toString()));
            newItem->setTextColor(1,QColor(152,152,152));
        }
        else if(newTache->getDate()==2){
            newItem->setText(1,QString(newTache->getDaterel().c_str()));
            newItem->setTextColor(1,QColor(152,152,152));
        }
        if(checked){
            newItem->setCheckState(0,Qt::Checked);
            newItem->setTextColor(0,QColor(58,157,35));
        }
        else {
            newItem->setCheckState(0,Qt::Unchecked);
        }

        xmlToTache(element->FirstChildElement(),newItem,newTache);

        element = element->NextSiblingElement();
    }
}


void FirstWindow::chargerXmlFinished(string fileName)
{
    const char * charfilename = fileName.c_str();
    TiXmlDocument doc(charfilename);
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
    if(text=="Nouvelle tâche"){
        popup();
    }
    if(text=="Valider les tâches finies"){
        confirmFinished();
    }
    else if(text=="Sauvegarder la liste"){
        sauvegarderSous();
    }
    else if(text=="Charger une liste"){
        chargerXml();
    }
    /*else if(text=="Charger un type de tâche"){
        chargerXmlTemplate();
    }*/
    else if(text=="Supprimer la liste"){
        popupDeleteList();
    }
    else if(text=="Quitter"){
        close();
    }
    else if(text=="Developper la liste"){
        arbo->expandAll();
    }
    else if(text=="Reduire la liste"){
        arbo->collapseAll();
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

void FirstWindow::enableButtons()
{
    finishedbutton->setEnabled(true);
    saveButton->setEnabled(true);
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
    else if (text=="Créer un type de tâche..."){
        if(item){
            defineCurrentTache(item,racine);
            widget_template * wt = new widget_template(currentTache,this,0);
            wt->show();
            currentTache = racine;
        }
    }
    else if(text=="Ajouter une étape"){
        if (item){
            popup(item,2);
        }
    }
    else if(text=="Supprimer"){
        if (item){
            popup(item,3);
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
    string stringnomFichier = "../Toudou/xml/"+nomFichier+".xml";
    const char * charnomfichier = stringnomFichier.c_str();
    TiXmlDocument doc(charnomfichier);

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
    const char * charnom("nom");
    const char * charnomvalue = item->text(0).toStdString().c_str();
    const char * chardate("date");
    const char * chardatevalue = item->text(1).toStdString().c_str();
    newElement->SetAttribute(charnom,charnomvalue);
    newElement->SetAttribute(chardate,chardatevalue);
    // TODO : modif avec les nouvelles dates
    // newElement->SetAttribute("date",date.toString().toStdString());
    element->LinkEndChild( newElement );

    for (int i=0 ; i<item->childCount() ; i++){
        QTreeWidgetItem * subItem = item->child(i);
        addItemInXml(doc,newElement,subItem);
    }
}

void FirstWindow::deleteList()
{
    for (int i = 0; i < arbo->topLevelItemCount(); ++i)
    {
        qDeleteAll(arbo->topLevelItem(i)->takeChildren());
        delete(arbo->topLevelItem(i));
        i--;
    }
    racine = new Tache("Toutes les taches");
    racine->setMatchingItem(arbo->invisibleRootItem());
}

void FirstWindow::popupDeleteList()
{
    QMessageBox * supprDiag = new QMessageBox();
    supprDiag->setWindowTitle("Supprimer la liste");
    supprDiag->addButton("Annuler",QMessageBox::RejectRole);
    supprDiag->addButton("Supprimer",QMessageBox::AcceptRole);

    supprDiag->setText("Attention, toutes les tâches de la liste vont être supprimées !");
    supprDiag->show();
    // le signal est bien "rejected", c est un bug Qt
    QObject::connect(supprDiag,SIGNAL(accepted()),this,SLOT(deleteList()));
}

void FirstWindow::deleteFinished()
{
    for (int i = 0; i < arboAchevees->topLevelItemCount(); ++i)
    {
        qDeleteAll(arboAchevees->topLevelItem(i)->takeChildren());
        delete(arboAchevees->topLevelItem(i));
        i--;
    }
}

void FirstWindow::todoToday()
{
    for (int i = 0; i < arbo->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem * item = arbo->topLevelItem(i);
        todoToday(item);
    }
}

void FirstWindow::todoToday(QTreeWidgetItem * item)
{
    QDate qdt = qdt.fromString(item->text(1));
    if(qdt==QDate::currentDate()){
        item->setTextColor(1,QColor(229,93,93));
    }
    for (int i=0 ; i<item->childCount() ; i++){
        QTreeWidgetItem * subItem = item->child(i);
        todoToday(subItem);
    }
}

QTreeWidgetItem* FirstWindow::checkedItem(QTreeWidget *tree)
{
    for(int i=0 ; tree->topLevelItemCount() ; i++){
        if(tree->topLevelItem(i)->checkState(0)==Qt::Checked){
            return tree->topLevelItem(i);
        }
    }
    return 0;
}
