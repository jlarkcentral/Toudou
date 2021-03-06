#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>
#include <QIcon>
#include <QAction>
#include <QPushButton>

#include <iostream>

#include "widget_infos.h"
#include "tache.h"

using namespace std;

class FirstWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();

    // l'arborescence devient un parametre global pour y acceder dans les slots
    QTreeWidget * arbo;
    QTreeWidget * arboAchevees;
    // l'objet courant dans l'arbre
    QTreeWidgetItem * currentItem;

    //icone "ajouter une sous-tache"
    QIcon * plusIcon;
    // icone supprimer la tache
    QIcon * supprIcon;

    // tache a la racine de toutes les taches courantes
    Tache * racine;
    Tache * currentTache;

    // vrai si l'arbre est developpé
    bool expand;

    QPushButton * newbutton;
    QPushButton * finishedbutton;
    QPushButton * saveButton;

    // menu clic droit
    QMenu * contextMenu;

    // liste templates
    Tache * templates;
    QTreeWidget * templatesTree;

    QStatusBar * statbar;

    // effacer les icones
    void eraseIcons(QTreeWidgetItem * item);

    void defineCurrentTache(QTreeWidgetItem * item, Tache *tacheRef);
    void confirmFinishedSubItems(QTreeWidgetItem * item);
    bool areSubItemsChecked(QTreeWidgetItem* item);
    void xmlToTache(TiXmlElement * element,QTreeWidgetItem *item,Tache * tache);
    void chargerXml(string fileName);
    void chargerXml(string fileName,QTreeWidgetItem * item,Tache * tacheRacine);
    void createXmlforTree(string nomFichier);
    void addItemInXml(TiXmlDocument doc,TiXmlElement * element,QTreeWidgetItem * item);
    void xmlToTacheFinished(TiXmlElement * element,QTreeWidgetItem *item);
    void chargerXmlFinished(string fileName);
    void popupDeleteList();
    void todoToday();
    void todoToday(QTreeWidgetItem *item);
    void sauvegarderTemplates();

    // Enlever les checkboxes des sous-taches
    void removeCheckboxes(QTreeWidgetItem * item);

    // Disable les sous-taches pour une meilleure visibilit� des templates
    void disableSubtasks(QTreeWidgetItem * item);

    QTreeWidgetItem *checkedItem(QTreeWidget * tree);

signals:
    void appClosed();
private:
    //bool drawerOpened;
    QGridLayout * mainLayout;

public slots:
    //void openDrawer();
    //void closeDrawer();
    void popup(); // dclench si bouton "Nouveau"
    void popup(QTreeWidgetItem* i, int n); // dclench si clic sur le "+" dans l'arbo
    void resetDisable(); // la fenetre principale revient active apres le popup Ajout
    void tacheChecked(QTreeWidgetItem* item,int n); // action quand la tache est checke
    void showIcons(QTreeWidgetItem* item,int n); // affiche les icones "plus" et "supprimer" quand on passe la souris
    void deleteItem(); // supprimer une tache
    void sauvegarderSous();
    void sauvegarderSession();
    void chargerXml();
    void chargerXmlTemplate();
    void menuAction(QAction* action);
    void confirmFinished();
    void enableButtons();
    void contextMenuAction(QAction * action);
    void creerTemplateSous();
    void showLineTabFinished(QTreeWidgetItem*,int);
    void deleteList();
    void deleteFinished();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // FIRSTWINDOW_H
