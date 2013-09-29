#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtGui>
#include <QWidget>
#include <QMainWindow>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDialogButtonBox>
#include <QStackedWidget>
#include <QListWidget>
#include <QRadioButton>
#include <QTextEdit>
#include <QLabel>
#include <QTextBrowser>
#include <QCheckBox>


namespace Ui {
class MainWindow;
}

struct Answer{
    int seq;
    QString a1;
    QString a2;
    QString a3;
    QString a4;
    int correct;
    QVector<QRadioButton*> rb;
    QListWidgetItem* icon;
    //Answer(){};
};

struct Literature{
    int seq;
    int type;
    QString url;
    QString description;
};

class GeneralMenu: public QWidget{
    Q_OBJECT

    QList<QPushButton*>button_list;
    QList<QPushButton*>control_button_list;
    QCheckBox* show_correct_answers;

public:
    GeneralMenu( const QMap<int, QString>& titles, QTabWidget* tab_widget, QWidget *parent=NULL);
    QCheckBox* getShowCorrectAnswers(){ return show_correct_answers;};

public slots:
    void test_selected(QAbstractButton* button);

signals:
    void selected_test(int, bool);
};

class Test:public QMainWindow{
    Q_OBJECT
    bool checked;
    bool is_control;
    QString title;
    QMap<int, QString> questions;
    QList <Answer> answers;
    QListWidgetItem* answer_button;
    QCheckBox* show_correct_answers_button;


public:
    Test(const int number ,const QString& title, const QMap<int, QString>& questions,
        const QList<Answer>& answers, const QList <Literature> & lits, const bool is_control, QCheckBox* show_correct_answers,
        QMainWindow* parent = NULL);

public slots:
    void check_answers(QListWidgetItem* item);
    void checkAnswers();
    void showCorrectAnswers();
    void closeEvent(QCloseEvent* event);
signals:
    void test_closed(Test*);
};

/*
class Control_Test:public Test{
public:
    Test(const int number ,const QString& title, const QMap<int, QString>& questions,
        const QList<Answer>& answers, const QList <Literature> & lits,
        QMainWindow* parent = NULL);
};
*/

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool InitialiseDB();
    void AddGeneralMenu();
    void AddTest(const int number, const bool is_control);
private:
    QMap<int, QString> titles;
    Ui::MainWindow *ui;
    QTabWidget* tab_widget;
    QSqlDatabase db;
    GeneralMenu* general_menu;
    QList <Test*> tests;
    //QString db_user;
    //QString db_password;
    void GetAllTitles(QMap<int, QString>& titles);
    void GetAllQuestions(const int number, QMap<int, QString>& questions, const bool is_control);
    void GetAllAnswers(const int number, QList<Answer> & answers, const bool is_control);
    void GetAllLiterature(const int number, QList<Literature> & lits);

public slots:
    void closeEvent(QCloseEvent* event);
    void selected_test(const int number, const bool is_control);
    void test_closed(Test* );
};


class GlobalTabbedWidget : public QWidget{
    Q_OBJECT;

    QStackedWidget * pages;
    QListWidget * tab_panel;
    QMap <QWidget*, QListWidgetItem*> tab; //indexes of pages to tab_panel indexes

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
public:
    GlobalTabbedWidget(QWidget * parent = NULL);
    QListWidgetItem* addTab( QWidget * widget, QString & name, QIcon icon, QColor color );
    void replaceTab(QWidget * w, int pos);
    void removeTab(QWidget *w);
};
#endif // MAINWINDOW_H
