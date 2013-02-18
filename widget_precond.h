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

using namespace std;

class widget_precond : public QWidget
{
    Q_OBJECT

public:
    explicit widget_precond(FirstWindow * fw, QWidget *parent = 0);
    ~widget_precond();
    vector<Tache> getPreconditions();

private:
    FirstWindow * FirstW;
    QTreeWidget * tree;
    vector<QTreeWidgetItem*> itemschecked;

public slots:
    void itemChecked(QTreeWidgetItem* item,int n);
};

#endif // WIDGET_PRECOND_H
