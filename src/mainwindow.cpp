#include "mainwindow.h"
#include "iostream"

#include "ListItemWidget.h"

#include <QVBoxLayout>
#include <QStringList>
#include <QDebug>




MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    listWidget = new QListWidget(this);
    auto *layout = new QVBoxLayout(this);
    layout->addWidget(listWidget);
    populateList(dataMap);
}

MainWindow::~MainWindow()
{
}


void MainWindow::populateList(std::map<QString, QString> objectMap) {

    this->layout()->removeWidget(listWidget);
    delete listWidget;

    listWidget = new QListWidget(this);
    this->layout()->addWidget(listWidget);

    listWidget->setSpacing(5);
    listWidget->setStyleSheet("QListWidget::item { margin: 5px; }");

    for (const auto &pair : objectMap) {
        const QString &name = pair.first;
        const QString &position = pair.second;
        auto *widget = new ListItemWidget(name, position);
        connect(widget, &ListItemWidget::buttonClicked, this, &MainWindow::onItemButtonClicked);
        connect(widget, &ListItemWidget::buttonClickedStop, this, &MainWindow::onItemButtonClickedStop);

        auto *listItem = new QListWidgetItem(listWidget);
        listItem->setSizeHint(widget->sizeHint());

        listWidget->addItem(listItem);
        listWidget->setItemWidget(listItem, widget);

        listWidget->setSpacing(5);
        listWidget->setStyleSheet("QListWidget::item { margin: 5px; }");
    }

    /*
     * int row = 0;
for (const auto &pair : objectMap) {
    const QString &name = pair.first;
    const QString &position = pair.second;

    if (row < listWidget->count()) {
        // Update existing widget
        auto *item = listWidget->item(row);
        auto *widget = qobject_cast<ListItemWidget*>(listWidget->itemWidget(item));
        if (widget) {
            widget->updateData(name, position); // you’ll need to implement this method in ListItemWidget
        }
    } else {
        // Add new widget
        auto *widget = new ListItemWidget(name, position);
        connect(widget, &ListItemWidget::buttonClicked, this, &MainWindow::onItemButtonClicked);
        connect(widget, &ListItemWidget::buttonClickedStop, this, &MainWindow::onItemButtonClickedStop);

        auto *listItem = new QListWidgetItem(listWidget);
        listItem->setSizeHint(widget->sizeHint());

        listWidget->addItem(listItem);
        listWidget->setItemWidget(listItem, widget);
    }

    ++row;
}

// Remove any extra items no longer needed
while (listWidget->count() > row) {
    delete listWidget->takeItem(listWidget->count() - 1);
}
*/
}

void MainWindow::setMonitor(MonitoringStation *monitoringStation) {
    monitor = monitoringStation;
}

void MainWindow::onItemButtonClicked(const QString &text) {
    //qDebug() << "Button clicked on" << text;
    monitor->buttonOverClicked(text);
}

void MainWindow::onItemButtonClickedStop(const QString &text) {
    //qDebug() << "Button clicked on Stop of" << text;
    monitor->buttonStopClicked(text);
}

void MainWindow::updateData(const QString &name, const QString &position) {
    dataMap[name] = position;
    populateList(dataMap);
}

