#ifndef WIDGET_AJOUT_H
#define WIDGET_AJOUT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "tache.h"
#include "firstwindow.h"

#include <iostream>

using namespace std;


class Widget_ajout : public QWidget
{
    Q_OBJECT

public:
    Widget_ajout(FirstWindow * fw ,QWidget *parent = 0);
    ~Widget_ajout();

    QLabel* getName();
    void setName(string s);

    QLabel* getParent();
    void setParent(string s);

    QLabel* getDate();
    void setDate(string s);

    QLabel* getTimeleft();
    void setTimeleft(string s);

    QLabel* getType();
    void setType(string s);

    FirstWindow * firstW;

private:
    QLabel * name;
    QLabel * parent;
    QLabel * date;
    QLabel * timeleft;
    QLabel * type;

public slots:
};

#endif // WIDGET_AJOUT_H
