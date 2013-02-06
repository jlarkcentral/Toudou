#ifndef WIDGET_AJOUT_H
#define WIDGET_AJOUT_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QCloseEvent>
#include <QCalendarWidget>

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

private:
    QLineEdit * name;
    QLabel * parent;
    QLabel * date;
    QCalendarWidget * calendar;
    QLabel * timeleft;
    QLabel * type;
    QPushButton * details;
    bool details_aff;
    QGroupBox * groupbox_date;

signals:
    void WidgetClosed();

public slots:
    void addTache();
    void afficherDate();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_AJOUT_H
