#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawerOpened = false;

    QObject::connect(ui->newButton,SIGNAL(clicked()),this,SLOT(openDrawer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openDrawer()
{
    if (!drawerOpened)
    {
        int size = width();
        for(int i=0 ; i<15 ; i++)
        {
            usleep(10000);
            size += 25;
            setFixedWidth(size);
        }
        drawerOpened = true;
    }
}

void MainWindow::closeDrawer()
{
    if (drawerOpened)
    {
        int size = width();
        for(int i=0 ; i<15 ; i++)
        {
            usleep(10000);
            size -= 25;
            setFixedWidth(size);
        }
        drawerOpened = false;
    }
}
