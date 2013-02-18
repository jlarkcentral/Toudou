#ifndef WIDGET_PRECOND_H
#define WIDGET_PRECOND_H

#include <sstream>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTreeWidget>
#include <QHeaderView>
#include <QLabel>
#include "firstwindow.h"


class widget_precond : public QWidget
{
    Q_OBJECT

public:
    explicit widget_precond(FirstWindow * fw, QWidget *parent = 0);
    ~widget_precond();

private:
    FirstWindow * FirstW;
    QTreeWidget * tree;

public slots:
    void itemChecked();
};

#endif // WIDGET_PRECOND_H
