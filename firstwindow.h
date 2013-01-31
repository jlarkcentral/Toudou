#ifndef FIRSTWINDOW_H
#define FIRSTWINDOW_H

#include <QMainWindow>

namespace Ui {
class FirstWindow;
}

class FirstWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit FirstWindow(QWidget *parent = 0);
    ~FirstWindow();
    
private:
    Ui::FirstWindow *ui;
    bool drawerOpened;

public slots:
    void openDrawer();
};

#endif // FIRSTWINDOW_H
