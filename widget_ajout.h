#ifndef WIDGET_AJOUT_H
#define WIDGET_AJOUT_H

#include <stdlib.h>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QCloseEvent>
#include <QCalendarWidget>

#include "tache.h"
#include "firstwindow.h"
#include "widget_date.h"

#include <iostream>

using namespace std;


class Widget_ajout : public QWidget
{
    Q_OBJECT

public:
    Widget_ajout(FirstWindow * fw ,QWidget *parent = 0);
    ~Widget_ajout();

    QString getName();
    void setName(QString s);

    QLabel* getParent();
    void setParent(string s);

    QLabel* getDate();
    void setDate(string s);

    QLabel* getTimeleft();
    void setTimeleft(string s);

    QLabel* getType();
    void setType(string s);

    FirstWindow * firstW;
    QPushButton * boutonAjout;
    QPushButton * boutonAnnul;

private:
    QLineEdit * name;
    QPushButton * date_plus;
    QLabel * afficher_date;
    bool date_aff;
    widget_date * dates;

signals:
    void WidgetClosed();

public slots:
    void addTache();
    void afficherDate();
    void textEdited(QString s);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_AJOUT_H
