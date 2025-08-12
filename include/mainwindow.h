#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPainter>
#include <QLabel>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>

#include <QWidget>
#include <QListWidget>
#include "monitoring_station.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct CarPos {
    double x, y;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void updateData(const QString &name, const QString &position);
    void setMonitor(MonitoringStation *monitoringStation);

private slots:
    void onItemButtonClicked(const QString &text);
    void onItemButtonClickedStop(const QString &text);

private:
    QListWidget *listWidget;
    void populateList(std::map<QString, QString> objectMap);
    std::map<QString, QString> dataMap;
    MonitoringStation *monitor;
};
#endif // MAINWINDOW_H
