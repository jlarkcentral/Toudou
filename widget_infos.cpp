#include "widget_infos.h"
#include "ui_widget_infos.h"

Widget_infos::Widget_infos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget_infos)
{
    ui->setupUi(this);
}

Widget_infos::~Widget_infos()
{
    delete ui;
}
