#include "mainwindow.h"
#include "monitoring_station.hpp"
#include "broadcast_receiver.hpp"

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QThread>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumSize(600, 400);

    w.show();

    MonitoringStation *m = new MonitoringStation();
    Receiver *recv = new Receiver(*m);

    QObject::connect(m, &MonitoringStation::dataReceived,
                     &w, &MainWindow::updateData);

    recv->start();

    w.setMonitor(m);


    return a.exec();
}
