#ifndef WIDGET_MODIF_H
#define WIDGET_MODIF_H

#include <stdlib.h>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QFormLayout>
#include <QCloseEvent>
#include <QCalendarWidget>
#include <QCheckBox>
#include <QFrame>

#include "tache.h"
#include "firstwindow.h"
#include "widget_date.h"
#include "widget_precond.h"
#include "widget_templ_aff.h"

#include <iostream>

using namespace std;


class Widget_modif : public QWidget
{
    Q_OBJECT

public:
    Widget_modif(QTreeWidgetItem * item, FirstWindow * fw ,QWidget *parent = 0);
    ~Widget_modif();

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

    QTreeWidgetItem * itemToModify;



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
    QWidget * ordon;
    QCheckBox * ordonch;
    QLabel * ordon_expl;
    QPushButton * template_plus;
    QLabel * afficher_template;
    bool template_aff;
    widget_templ_aff * templ;

signals:
    void WidgetClosed();

public slots:
    void addTache();
    void afficherDate();
    void textEdited(QString s);
    void afficherPrecond();
    void afficherOrdon();
    void afficherTempl();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_MODIF_H
