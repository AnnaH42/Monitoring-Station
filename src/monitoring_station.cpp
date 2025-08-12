#include "monitoring_station.hpp"
#include <boost/json/src.hpp>


    MonitoringStation::MonitoringStation(QObject *parent)
    : QObject(parent) {
    }

    void MonitoringStation::receivedMessage(char* message, char* address) {
        // deserialise
        Car newCar = MonitoringStation::deserialiseFromJson(message);

        bool found = false;
        for (std::list<Car>::iterator it = listOfCars.begin(); it != listOfCars.end(); ++it) {
            if ((*it).name == newCar.name) {
                if (((*it).timeSec == newCar.timeSec && (*it).timeNSec < newCar.timeNSec) || ((*it).timeSec < newCar.timeSec)) {
                    (*it) = newCar;
                }
                found = true;
            }
        }
        if (!found) {
            listOfCars.push_back(newCar);
            mapOfIPs.insert({newCar.name, address});
        }

        QString name = QString::fromStdString(newCar.name);
        QString position = "x: " + QString::number(newCar.positionX) + "; y: " + QString::number(newCar.positionY);

        emit dataReceived(name, position);
    }


    void MonitoringStation::buttonOverClicked(const QString &text) {
        std::string name = text.toStdString();
        std::string address = mapOfIPs[name];

        Car monitor;
        monitor.overtaking = true;

        MonitoringStation::prepareMessage(monitor, address);
    }

    void MonitoringStation::buttonStopClicked(const QString &text) {
        std::string name = text.toStdString();
        std::string address = mapOfIPs[name];

        Car monitor;
        monitor.stop = true;

        MonitoringStation::prepareMessage(monitor, address);

    }

    void MonitoringStation::prepareMessage(Car& monitor, std::string address) {
        Unicast sender;

        timespec time;
        //std::timespec_get(&time, TIME_UTC);
        monitor.timeSec = time.tv_sec;
        monitor.timeNSec = time.tv_nsec;
        boost::json::value jv = MonitoringStation::denmToJson(monitor);
        std::string jsonStr = boost::json::serialize(jv);
        std::cout << "JSON object created" << std::endl;

        char* buffer = new char[jsonStr.size() + 1];
        std::memcpy(buffer, jsonStr.c_str(), jsonStr.size() + 1);
        sender.sendMessageTo(buffer, address, jsonStr.size());
    }

    boost::json::value MonitoringStation::denmToJson(Car& car) {
        boost::json::object data = {
            {"name", car.name},
            {"positionX", car.positionX},
            {"positionY", car.positionY},
            {"direction", car.direction},
            {"time in seconds", car.timeSec},
            {"time in nanoseconds", car.timeNSec},
            {"overtaking", car.overtaking},
            {"emergency stop", car.stop}
        };
        return boost::json::object{
            {"DENM", data}
        };
    }


    Car MonitoringStation::deserialiseFromJson(const std::string& json_str) {
        boost::json::value jv = boost::json::parse(json_str);

        if (!jv.is_object())
            throw std::runtime_error("Top-level JSON is not an object");

        const boost::json::object& obj = jv.as_object();



        auto it = obj.find("DENM");

        if (it->value().is_object()) {
            const boost::json::object& car_obj = it->value().as_object();
            Car car;
            //car.name = boost::json::value_to<std::string>(car_obj.at("name"));
            //car.positionX = boost::json::value_to<float>(car_obj.at("positionX"));
            //car.positionY = boost::json::value_to<float>(car_obj.at("positionY"));
            //car.direction = boost::json::value_to<int>(car_obj.at("direction"));
            //Car car(boost::json::value_to<std::string>(car_obj.at("name")), boost::json::value_to<float>(car_obj.at("positionX")),
            //        boost::json::value_to<float>(car_obj.at("positionY")), boost::json::value_to<int>(car_obj.at("direction")), boost::json::value_to<time_t>(car_obj.at("time in seconds")),
            //        boost::json::value_to<long>(car_obj.at("time in nanoseconds")), boost::json::value_to<bool>(car_obj.at("overtaking")),
            //        boost::json::value_to<bool>(car_obj.at("emergency stop")));
            //std::cout << "Deserialised data" << std::endl;
            return car;
        }
        auto it2 = obj.find("CAM");
        const boost::json::object& car_obj = it2->value().as_object();
        Car car(boost::json::value_to<std::string>(car_obj.at("name")), boost::json::value_to<float>(car_obj.at("positionX")),
                boost::json::value_to<float>(car_obj.at("positionY")), boost::json::value_to<int>(car_obj.at("direction")), boost::json::value_to<time_t>(car_obj.at("time in seconds")),
                boost::json::value_to<long>(car_obj.at("time in nanoseconds")));

        return car;
    }




