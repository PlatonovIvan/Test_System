#include "mainwindow.h"
#include <QApplication>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow main_window;
    main_window.setWindowIcon(QIcon("/home/ivan/static/logo_small.gif"));
    main_window.setWindowTitle("Автоматизированная система контроля знаний");
    bool ok = main_window.InitialiseDB();
    if (!ok){
        QMessageBox mb(QMessageBox::Warning, "Error in program", "Error in database. Try to restart program.", QMessageBox::Ok);
        mb.exec();
        return -1;
    }
    main_window.AddGeneralMenu();
    main_window.show();
    return a.exec();
}
