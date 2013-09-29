#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tab_widget = new QTabWidget(this);
    //tab_widget->addTab(" df ", (new(QWidget)));
    setCentralWidget(tab_widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool MainWindow::InitialiseDB(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug()<<QCoreApplication::applicationDirPath();
    QString db_name=QCoreApplication::applicationDirPath()+"/test.db";
    qDebug()<<db_name;
    db.setDatabaseName( db_name );
    //db.setUserName( "admin" );
    //db.setPassword( "my_pretty_economics" );
    bool ok = db.open();
    return ok;
}

void MainWindow::GetAllTitles(QMap<int, QString>& titles){

    QSqlQuery q("select distinct theme_seq, title from Titles order by theme_seq, title;", db);

    if (!q.exec()){
        QMessageBox mb(QMessageBox::Warning, "Error in SqlQuery", "Error in database. Try to restart the program.", QMessageBox::Ok);
        mb.exec();
    }
    else{
        while(q.next()){
            titles.insert(q.value(0).toUInt(), q.value(1).toString());
        }

    }
    return;
}


void MainWindow::GetAllQuestions(const int number, QMap<int, QString>& questions, const bool is_control){
    QString table;
    if (is_control)
        table="Control_Questions";
    else
        table="Questions";

    QString sql_query = QString("select q_seq, question from %2 \
                                 where (theme_seq=%1) order by q_seq;").arg(number).arg(table);
    QSqlQuery q(sql_query, db);

    if (!q.exec()){
        QMessageBox mb(QMessageBox::Warning, "Error in SqlQuery", "Error in database. Try to restart the program.", QMessageBox::Ok);
        mb.exec();
    }
    else{
        while(q.next()){
            questions.insert(q.value(0).toUInt(), q.value(1).toString());
            qDebug()<<q.value(0).toUInt()<< q.value(1).toString();
        }
    }
    return;
}

void MainWindow::GetAllAnswers(const int number, QList<Answer>& answers, const bool is_control){
    QString table;
    if (is_control)
        table="Control_Answers";
    else
        table="Answers";

    QString sql_query = QString("select q_seq, a1, a2, a3, a4, correct \
                                from %2 where (theme_seq=%1) order by q_seq;").arg(number).arg(table);
    QSqlQuery q(sql_query, db);

    if (!q.exec()){
        QMessageBox mb(QMessageBox::Warning, "Error in SqlQuery",
                        "Error in database. Try to restart the program.", QMessageBox::Ok);
        mb.exec();
    }
    else{
        while(q.next()){
            Answer answer;
            answer.seq=q.value(0).toUInt();
            answer.a1=q.value(1).toString();
            answer.a2=q.value(2).toString();
            answer.a3=q.value(3).toString();
            answer.a4=q.value(4).toString();
            answer.correct=q.value(5).toUInt();
            answers.append(answer);
            //qDebug()<<q.value(0).toUInt()<< q.value(1).toString();
        }
    }
    return;
}

void MainWindow::GetAllLiterature(const int number, QList<Literature>& lits){
    QString sql_query = QString("select lit_seq, type, url, description from Literature where (theme_seq=%1) order by lit_seq, type;").arg(number);
    QSqlQuery q(sql_query, db);

    if (!q.exec()){
        QMessageBox mb(QMessageBox::Warning, "Error in SqlQuery", "Error in database. Try to restart the program.", QMessageBox::Ok);
        mb.exec();
    }
    else{
        while(q.next()){
            Literature lit;
            lit.seq=q.value(0).toUInt();
            lit.type=q.value(1).toUInt();
            lit.url=q.value(2).toString();
            lit.description=q.value(3).toString();
            lits.append(lit);
            //qDebug()<<q.value(0).toUInt()<< q.value(1).toString();
        }
    }
    return;
}



void MainWindow::closeEvent(QCloseEvent* event){
    if(not tests.isEmpty()){ //and (test->isActive())){

        QPushButton* okButton = new QPushButton("OK");
        QPushButton* cancelButton = new QPushButton("Отмена");
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning, "Предупреждение.",
                                        "Вы выполняете тестирование. Все результаты незавершенных тестов будут потеряны. Продолжить?");
        mb->addButton(okButton, QMessageBox::AcceptRole);
        mb->addButton(cancelButton, QMessageBox::RejectRole);
        mb->exec();
        if (mb->clickedButton()==okButton)
            event->accept();
        else
            event->ignore();
    }

}

void MainWindow::AddGeneralMenu(){
    //QMap<int, QString> titles;
    if (not titles.empty())
        titles.clear();
    GetAllTitles(titles);
    general_menu=new GeneralMenu( titles, tab_widget, this);
}


void MainWindow::AddTest(const int number, const bool is_control){
    QMap<int, QString> questions;
    QList <Answer> answers;
    QList <Literature> lits;
    QString title;
    if (not is_control){
        title = titles.find(number).value();
        if (number!=15){
            GetAllQuestions(number, questions, is_control);
            GetAllAnswers(number, answers, is_control);
        }
        GetAllLiterature(number, lits);
        //Test* test = new Test(number, title, questions, answers, lits, is_control, this);
        //connect(test, SIGNAL(test_closed(Test*)), this, SLOT(test_closed(Test*)));
        //tests.append(test);
    }
    else{
        if (number==1)
            title="Контрольный тест 1";
        else if (number==2)
            title="Контрольный тест 2";
        else
            return;

        GetAllQuestions(number, questions, is_control);
        GetAllAnswers(number, answers, is_control);

        //Test* test = new Test(number, title, questions, answers, lits, is_control, show_correct_answers, this);
        //connect(test, SIGNAL(test_closed(Test*)), this, SLOT(test_closed(Test*)));
        //tests.append(test);
    }
    Test* test = new Test(number, title, questions, answers, lits, is_control, general_menu->getShowCorrectAnswers(), this);
    connect(test, SIGNAL(test_closed(Test*)), this, SLOT(test_closed(Test*)));
    tests.append(test);

}


void MainWindow::selected_test(const int number, const bool is_control){
    AddTest(number, is_control);
}

void MainWindow::test_closed( Test* test){
    tests.removeOne(test);
}
