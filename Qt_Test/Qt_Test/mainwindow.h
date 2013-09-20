#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}


class GeneralMenu: public QWidget{
    Q_OBJECT

public:
    GeneralMenu(QWidget *parent);
};

class Test:public QWidget{
    Q_OBJECT

public:
    Test(const int number);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GeneralMenu general_menu;
    QString db_user;
    QString db_password;
    void InitialiseDB();
};


#endif // MAINWINDOW_H
