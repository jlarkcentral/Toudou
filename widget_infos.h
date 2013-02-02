#ifndef WIDGET_INFOS_H
#define WIDGET_INFOS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

#include "firstwindow.h"
#include "tache.h"

#include <iostream>

using namespace std;


class Widget_infos : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget_infos(Tache * t, QWidget *parent = 0);
    ~Widget_infos();

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
    
private:
    QLabel * name;
    QLabel * parent;
    QLabel * date;
    QLabel * timeleft;
    QLabel * type;

public slots:
};

#endif // WIDGET_INFOS_H
