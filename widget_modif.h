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

#include "tache.h"
#include "firstwindow.h"
#include "widget_date.h"

#include <iostream>

using namespace std;


class Widget_modif : public QWidget
{
    Q_OBJECT

public:
    Widget_modif(QTreeWidgetItem *item ,FirstWindow *fw, QWidget *parent);
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
    QPushButton * boutonModif;
    QTreeWidgetItem * itemToModify;

private:
    QLineEdit * name;
    QPushButton * date_plus;
    bool date_aff;
    widget_date * dates;

signals:
    void WidgetClosed();

public slots:
    void modifTache();
    void afficherDate();
    void textEdited(QString s);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_MODIF_H

