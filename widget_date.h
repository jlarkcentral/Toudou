#ifndef WIDGET_DATE_H
#define WIDGET_DATE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QRadioButton>
#include <QCalendarWidget>
#include <QTimeEdit>
#include <QComboBox>


class widget_date : public QWidget
{
    Q_OBJECT
    
public:
    explicit widget_date(QWidget *parent = 0);
    ~widget_date();
    
private:
    QWidget * abswidget;
    QWidget * relwidget;

public slots:
    void afficher_abs();
    void afficher_rel();
};

#endif // WIDGET_DATE_H
