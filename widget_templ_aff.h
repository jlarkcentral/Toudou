#ifndef WIDGET_TEMPL_AFF_H
#define WIDGET_TEMPL_AFF_H

#include "firstwindow.h"
#include <QTreeWidget>
#include <QLabel>
#include <QHeaderView>

class widget_templ_aff : public QWidget
{
    Q_OBJECT

public:
    explicit widget_templ_aff(FirstWindow * fw, QWidget *parent = 0);
    ~widget_templ_aff();

private:
    FirstWindow * FirstW;
    QTreeWidget * tree;
};

#endif // WIDGET_TEMPL_AFF_H
