#include <mainwindow.h>

void GlobalTabbedWidget:: changePage(QListWidgetItem *current, QListWidgetItem *previous){
    if (!current)
        current = previous;

    pages->setCurrentIndex(tab_panel->row(current));
}

GlobalTabbedWidget::GlobalTabbedWidget(QWidget* parent):QWidget(parent){
    pages = new QStackedWidget(this);
    tab_panel = new QListWidget(this);
    tab_panel->setMaximumWidth(150);
    tab_panel->setViewMode(QListView::IconMode);
    tab_panel->setIconSize(QSize(32, 32));
    tab_panel->setMovement(QListView::Static);
    tab_panel->setSpacing(12);

    QHBoxLayout * layout = new QHBoxLayout(this);
    setLayout(layout);

    layout->addWidget(tab_panel);
    layout->addWidget(pages);

    connect(tab_panel,
        SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
        this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
    connect ( tab_panel, SIGNAL(itemClicked(QListWidgetItem*)),
                parent, SLOT(check_answers(QListWidgetItem*)));
}


QListWidgetItem* GlobalTabbedWidget::addTab( QWidget * widget, QString & name, QIcon icon, QColor color){
    if( !widget )
        return NULL;

    QListWidgetItem * widget_item = new QListWidgetItem(tab_panel);
    widget_item->setText(name);
    widget_item->setIcon(icon);
    widget_item->setToolTip(name);
    widget_item->setTextAlignment(Qt::AlignHCenter);
    QBrush brush(color);
    widget_item->setBackground(brush);
    tab_panel->addItem( widget_item );
    pages->addWidget(widget);

    tab[widget] = widget_item;
    return widget_item;
}

void GlobalTabbedWidget::replaceTab(QWidget * w, int pos){
    int prev_pos = tab_panel->row(tab[w]);
    if (prev_pos == pos)
        return;
    pages->removeWidget(w);
    QListWidgetItem* item = tab_panel->takeItem(prev_pos);
    if (prev_pos > pos){
        tab_panel->insertItem(pos, item);
        pages->insertWidget(pos, w);
    }
    else{
        tab_panel->insertItem(pos - 1, item);
        pages->insertWidget(pos - 1, w);
    }
}
void GlobalTabbedWidget::removeTab(QWidget *w){
    pages->removeWidget(w);
    delete tab[w];
}
