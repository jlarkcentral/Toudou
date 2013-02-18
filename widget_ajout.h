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
#include <QCheckBox>

#include "tache.h"
#include "firstwindow.h"
#include "widget_date.h"
#include "widget_precond.h"

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
    QPushButton * precond_plus;
    QLabel * afficher_precond;
    bool precond_aff;
    widget_precond * preconds;
    QPushButton * ordon_plus;
    QLabel * afficher_ordon;
    bool ordon_aff;
    QCheckBox * ordon;
    QLabel * ordon_expl;

signals:
    void WidgetClosed();

public slots:
    void addTache();
    void afficherDate();
    void textEdited(QString s);
    void afficherPrecond();
    void afficherOrdon();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_AJOUT_H
