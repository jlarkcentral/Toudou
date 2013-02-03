#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QTreeWidget>

#include <iostream>

using namespace std;

class FirstWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();

    QTreeWidget * arbo;
    
private:
    bool drawerOpened;
    QGridLayout * mainLayout;


public slots:
    void openDrawer();
    void closeDrawer();
    void addTache();
};

#endif // FIRSTWINDOW_H
