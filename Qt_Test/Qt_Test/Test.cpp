#include <mainwindow.h>

Test::Test(const int number, const QString & title, const QMap<int, QString> & questions,
            const QList <Answer>& answers, const QList<Literature> & lits, const bool is_control,
            QCheckBox* show_correct_answers, QMainWindow *parent):
            title(title), questions(questions), answers(answers),
            checked(false), is_control(is_control), show_correct_answers_button(show_correct_answers), QMainWindow(parent){

    this->setWindowTitle(title);
    GlobalTabbedWidget* global = new GlobalTabbedWidget(this);
    //connect (globa, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(closeEvent(QCloseEvent*)));
    QWidget* question;
    int q_number;
    int i;
    QString q_name;
    QColor color(Qt::white);
    if (number!=15){
        for (QMap<int, QString>::const_iterator it = questions.begin(); it!=questions.end(); it++){
            q_name="Вопрос";
            question = new QWidget(global);
            QVBoxLayout* v_layout = new QVBoxLayout(question);
            QLabel* text_label = new QLabel(it.value(), this);
            v_layout->addWidget(text_label);
            q_number=it.key();
            bool flag=false;
            for (i=0; i< answers.size(); i++){
                if (answers[i].seq==q_number){
                    if (not this->answers[i].rb.empty())
                        this->answers[i].rb.clear();

                    QRadioButton* rb1 = new QRadioButton(answers[i].a1, question);
                    //rb1->setBackgroundRole(QPalette::HighlightedText);
                    /*
                    QPalette* palette = new QPalette();
                    palette->setColor(QPalette::ButtonText, Qt::red);
                    rb1->setPalette(*palette);
                    */
                    this->answers[i].rb.append(rb1);
                    QRadioButton* rb2 = new QRadioButton(answers[i].a2, question);
                    this->answers[i].rb.append(rb2);
                    QRadioButton* rb3 = new QRadioButton(answers[i].a3, question);
                    this->answers[i].rb.append(rb3);
                    QRadioButton* rb4 = new QRadioButton(answers[i].a4, question);
                    this->answers[i].rb.append(rb4);
                    v_layout->addWidget(rb1);
                    v_layout->addWidget(rb2);
                    v_layout->addWidget(rb3);
                    v_layout->addWidget(rb4);
                    flag=true;
                    break;
                }
                if (flag)
                    break;
            }
            q_name+=(" " + QString::number(q_number));
            this->answers[i].icon=global->addTab(question, q_name, QIcon(":images/logo_small.gif"), color);
        }
    }
    QString file_path = "/home/ivan/static/";
    if (not is_control){
    //Additional Questions

        QString filename=file_path+ "Theme" + (QString::number(number) + ".html");
        QTextBrowser* doc = new QTextBrowser(global);
        doc->setReadOnly(false);
        QFile file(filename);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream read_file(&file);
        doc->setHtml(read_file.readAll());
        doc->setTextInteractionFlags(Qt::TextSelectableByMouse);
        doc->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        doc->setOpenExternalLinks(true);
        //doc->setOpenLinks(true);
        QString add_q_tab = "Дополнительные \n задания";
        global->addTab( doc, add_q_tab, QIcon(), color);

    //Literature tab
        QWidget* literature = new QWidget(global);
        QVBoxLayout* v_layout = new QVBoxLayout(literature);
        QString l;
        QString e;
        QString u;
        for (int i = 0; i<lits.size(); i++){
            if (lits[i].type==1){
                if (l.isEmpty())
                    l="<h2>ЛИТЕРАТУРА:</h2> <ol>";
                l+=(" <li> " + lits[i].description);
                if (not lits[i].url.isEmpty())
                    l+= (" <a href= " + lits[i].url + " >" + lits[i].url +" </a>");
                l+="</li>";
            }
            else if (lits[i].type==2){
                if (e.isEmpty())
                e="<h2>СОЧИНЕНИЯ:</h2> <ol>";
                e+=(" <li> " + lits[i].description);
                if (not lits[i].url.isEmpty())
                    e+= (" <a href= " + lits[i].url + " >" + lits[i].url + " </a>");
                e+="</li>";
            }
            else if (lits[i].type==3){
                if (u.isEmpty())
                    u = "<h2>ИНТЕРНЕТ ИСТОЧНИКИ:</h2> <ol>";
                u+=(" <li> " + lits[i].description);
                if (not lits[i].url.isEmpty())
                    u= u + (" <a href= " + lits[i].url + " >" + lits[i].url + " </a>");
                u+="</li>";
            }
        }
        if (not l.isEmpty()){
            l+="</ol>";
            QTextBrowser* lit = new QTextBrowser(literature);
            lit->setHtml(l);
            lit->setTextInteractionFlags(Qt::TextSelectableByMouse);
            lit->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
            //lit->setTextFormat(Qt::RichText);
            lit->setOpenExternalLinks(true);
            v_layout->addWidget(lit);
        }
        if (not e.isEmpty()){
            e+="</ol>";
            QTextBrowser* essay = new QTextBrowser(literature);
            essay->setHtml(e);
            essay->setTextInteractionFlags(Qt::TextSelectableByMouse);
            essay->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
            //essay->setTextFormat(Qt::RichText);
            essay->setOpenExternalLinks(true);
            v_layout->addWidget(essay);
        }
        if (not u.isEmpty()){
            u+="</ol>";
            QTextBrowser* urls = new QTextBrowser(literature);
            urls->setHtml(u);
            urls->setTextInteractionFlags(Qt::TextSelectableByMouse);
            urls->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
            //urls->setTextFormat(Qt::RichText);
            urls->setOpenExternalLinks(true);
            v_layout->addWidget(urls);
        }

        QString lit_title="Источники\n информации";
        global->addTab( literature, lit_title, QIcon(":images/logo_small.gif"), color);
    }
    QWidget* check = new QWidget(global);
    color= QColor("#FFFF33");
    QString final_string = "Завершить\n тестирование";
    answer_button=global->addTab( check, final_string, QIcon(":images/logo_small.gif"), color);

    QString icon_name = file_path+QString::number(number)+".png";
    qDebug()<<"Icon_name"<<icon_name;
    this->setWindowIcon(QIcon(icon_name));
    this->setCentralWidget(global);
    this->show();
}



void Test::showCorrectAnswers(){

}


void Test::check_answers(QListWidgetItem* item){
    if (item==answer_button){
        QPushButton* okButton = new QPushButton("OK");
        QPushButton* cancelButton = new QPushButton("Отмена");
        QMessageBox* mb = new QMessageBox(QMessageBox::Question, "Завершение тестирования",
                                        "Вы уверены, что хотите завершить тестирование?");
        mb->addButton(okButton, QMessageBox::AcceptRole);
        mb->addButton(cancelButton, QMessageBox::RejectRole);
        mb->exec();
        if (mb->clickedButton()==okButton)
            checkAnswers();
    }
}

void Test::checkAnswers(){
    bool show_correct=false;
    if (show_correct_answers_button != NULL){
        if ( (not is_control) and (show_correct_answers_button->checkState()==Qt::Checked )){
            show_correct=true;
        }
    }
    qDebug()<<"Show Correct="<<show_correct;
    checked = true;
    int correct;
    for (int i=0; i<answers.size(); i++){
        qDebug()<<"Answer="<<answers[i].correct;
        correct=0;
        for (int j=0; j<answers[i].rb.size(); j++){
            if (answers[i].rb[j]->isChecked()){
                correct=j+1;
                break;
            }
        }
        if (answers[i].correct==correct){
            QColor green("#33FF00");
            QPalette pal = answers[i].rb[correct]->palette();
            pal.setColor(QPalette::Active, QPalette::ButtonText, QColor(""));
            answers[i].rb[correct]->setPalette(pal);
            QBrush brush(green);
            answers[i].icon->setBackground(brush);
        }
        else{
            QColor red("#FF0000");
            QPalette pal = answers[i].rb[correct]->palette();
            pal.setColor(QPalette::Active, QPalette::ButtonText, QColor(""));
            answers[i].rb[correct]->setPalette(pal);
            QBrush brush(red);
            answers[i].icon->setBackground(brush);
        }
    }
}


void Test::closeEvent(QCloseEvent* event){
    if( not checked){

        QPushButton* okButton = new QPushButton("OK");
        QPushButton* cancelButton = new QPushButton("Отмена");
        QMessageBox* mb = new QMessageBox(QMessageBox::Warning, "Предупреждение.",
                                        "Вы выполняете тестирование. Результаты теста будут потеряны. Продолжить?");
        mb->addButton(okButton, QMessageBox::AcceptRole);
        mb->addButton(cancelButton, QMessageBox::RejectRole);
        mb->exec();
        if (mb->clickedButton()==okButton){
            emit test_closed(this);
            event->accept();
        }
        else{
            event->ignore();
        }
    }

}
