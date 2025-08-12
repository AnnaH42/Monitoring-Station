#include "car.hpp"


Car::Car(std::string name, float positionX, float positionY, int direction, time_t timeSec, long timeNSec, bool overtaking, bool stop) {
    this->name = name;
    this->positionX = positionX;
    this->positionY = positionY;
    this->direction = direction;
    this->timeSec = timeSec;
    this->timeNSec = timeNSec;
    this->overtaking = overtaking;
    this->stop = stop;
}

Car::Car() {
    this->name = "Monitoring Station";
    this->positionX = 0;
    this->positionY = 0;
    this->direction = 0;
    this->overtaking = false;
    this->stop = false;
}
