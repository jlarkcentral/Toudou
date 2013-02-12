#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>

#include <iostream>

#include "widget_infos.h"

using namespace std;

class FirstWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();

    // l'arborescence devient un parametre global pour y acceder dans les slots
    QTreeWidget * arbo;
    QTreeWidgetItem * currentItem;

    bool boolTest;
    
private:
    //bool drawerOpened;
    QGridLayout * mainLayout;

public slots:
    //void openDrawer();
    //void closeDrawer();
    void popup(); // déclenché si bouton "Nouveau"
    void popup(QTreeWidgetItem* i, int n); // déclenché si clic sur le "+" dans l'arbo
    void resetDisable();
    void tacheChecked(QTreeWidgetItem* item,int n);
};

#endif // FIRSTWINDOW_H
