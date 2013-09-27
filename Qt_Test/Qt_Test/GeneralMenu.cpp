#include<mainwindow.h>

GeneralMenu::GeneralMenu(const QMap<int, QString>& titles, QTabWidget* tab_widget, QWidget* parent):
                                                            QWidget(parent){
    QObject::connect(this, SIGNAL(selected_test(int, bool)), parent, SLOT(selected_test(const int, const bool)));

// SIMPLE TESTS
    QWidget* training_widget = new QWidget(tab_widget);
    QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    training_widget->setSizePolicy(policy);
    QGridLayout* gr_la = new QGridLayout(training_widget);
    QDialogButtonBox * button_box = new QDialogButtonBox(Qt::Vertical , training_widget);
    QObject::connect(button_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(test_selected(QAbstractButton* )));
    QPushButton* pb;
    QString button_name;
    QString number;
    for (QMap<int, QString>::const_iterator it=titles.begin(); it != titles.end(); it++){
        button_name="Глава";
        number=QString::number(it.key());
        button_name+=(" " + number +": "+ it.value());
        pb = new QPushButton(button_name, button_box);
        button_list.append(pb);
        button_box->addButton(pb, QDialogButtonBox::AcceptRole);
    }
    gr_la->addWidget(button_box);
    show_correct_answers = new QCheckBox("Показывать правильные ответы", training_widget);
    gr_la->addWidget(show_correct_answers);
    tab_widget->addTab(training_widget, "Тренировочные тесты"); //ICON

//CONTROL TESTS
    QWidget* control_widget = new QWidget(tab_widget);
    QSizePolicy control_policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    control_widget->setSizePolicy(control_policy);
    QGridLayout* control_gr_la = new QGridLayout(control_widget);
    QDialogButtonBox * control_button_box = new QDialogButtonBox(Qt::Vertical , control_widget);
    QObject::connect(control_button_box, SIGNAL(clicked(QAbstractButton*)), this, SLOT(test_selected(QAbstractButton* )));
    QPushButton* control_pb;

    control_pb = new QPushButton("Контрольный тест 1", control_button_box);
    control_button_list.append(control_pb);
    control_button_box->addButton(control_pb, QDialogButtonBox::AcceptRole);
    //Two
    control_pb = new QPushButton("Контрольный тест 2", control_button_box);
    control_button_list.append(control_pb);
    control_button_box->addButton(control_pb, QDialogButtonBox::AcceptRole);

    gr_la->addWidget(control_button_box);
    tab_widget->addTab(control_button_box, "Контрольные тесты"); //ICON
    return;
}


void GeneralMenu::test_selected(QAbstractButton* button){
    int number=0;
    for (QList<QPushButton*>::const_iterator it=button_list.begin(); it!=button_list.end(); it++, number++){
        if ((*it)==button){
            emit selected_test(number+1, false);
            return;
        }
    }
    number=0;
    for (QList<QPushButton*>::const_iterator it=control_button_list.begin(); it!=control_button_list.end(); it++, number++){
        if ((*it)==button){
            emit selected_test(number+1, true);
            return;
        }
    }
}
