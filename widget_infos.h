#ifndef WIDGET_INFOS_H
#define WIDGET_INFOS_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class Widget_infos;
}

class Widget_infos : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget_infos(QWidget *parent = 0);
    ~Widget_infos();
    
private:
    Ui::Widget_infos *ui;
    QLabel * name;
    QLabel * parent;
    QLabel * date;
    QLabel * timeleft;
    QLabel * type;
};

#endif // WIDGET_INFOS_H
