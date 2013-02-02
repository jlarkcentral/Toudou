#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <iostream>

using namespace std;

class FirstWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    
private:
    bool drawerOpened;
    QGridLayout * mainLayout;

public slots:
    void openDrawer();
};

#endif // FIRSTWINDOW_H
