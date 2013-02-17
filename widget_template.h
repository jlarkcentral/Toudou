#ifndef WIDGET_TEMPLATE_H
#define WIDGET_TEMPLATE_H

#include <QWidget>

#include "firstwindow.h"

class widget_template : public QWidget
{
    Q_OBJECT
public:
    explicit widget_template(Tache *tacheRacine,FirstWindow *fw, QWidget *parent);
    ~widget_template();
    FirstWindow * firstW;
    QLineEdit * nomFichierEdit;
    Tache * root;

signals:
    void WidgetClosed();
public slots:
    void saveXml();

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // WIDGET_TEMPLATE_H
