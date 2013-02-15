#ifndef WIDGET_SAUVEGARDE_H
#define WIDGET_SAUVEGARDE_H

#include <QWidget>

#include "firstwindow.h"

class widget_sauvegarde : public QWidget
{
    Q_OBJECT
public:
    explicit widget_sauvegarde(FirstWindow *fw,QWidget *parent = 0);

    FirstWindow * firstW;
    
signals:
    
public slots:
    
};

#endif // WIDGET_SAUVEGARDE_H
