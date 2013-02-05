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
    
private:
    bool drawerOpened;
    QGridLayout * mainLayout;


public slots:
    void openDrawer();
    void closeDrawer();
    //void addTache();
    void popAjout(); // d�clench� si bouton "Nouveau"
    void popAjout(QTreeWidgetItem* i, int column); // d�clench� si clic sur le "+" dans l'arbo
};

#endif // FIRSTWINDOW_H
