#ifndef MONITORING_STATION_HPP
#define MONITORING_STATION_HPP

#include <string>
#include <list>
#include <map>
#include <QObject>
#include <QString>
#include <QDebug>
#include "car.hpp"
#include "unicast_sender.hpp"
#include <sstream>
#include <ctime>
#include <chrono>

#include "boost/json.hpp"


class MonitoringStation : public QObject {
    Q_OBJECT

private:
    std::list<Car> listOfCars;
    std::map<std::string, std::string> mapOfIPs; //name of car, IP Adress

public:
    MonitoringStation(QObject *parent = nullptr);
    ~MonitoringStation() = default;

    void receivedMessage(char* message, char* address);

signals:
    void dataReceived(const QString &name, const QString &position);

public slots:
    void buttonOverClicked(const QString &text);
    void buttonStopClicked(const QString &text);
    boost::json::value denmToJson(Car& car);
    Car deserialiseFromJson(const std::string& json_str);
    void prepareMessage(Car& car, std::string address);
};

#endif // MONITORING_STATION_HPP
