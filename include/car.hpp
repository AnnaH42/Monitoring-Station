#ifndef CAR_HPP
#define CAR_HPP

#include <string>

#include <ctime>
#include <chrono>



class Car
{
public:
    /* data */
    std::string name;
    float positionX;
    float positionY;
    int direction;
    bool overtaking;
    bool stop;
    long timeNSec;
    time_t timeSec;



public:
    explicit Car(std::string name, float positionX, float positionY, int direction, time_t timeSec, long timeNSec, bool overtaking=false, bool stop = false);
    ~Car() = default;
    Car();
};

#endif // CAR_HPP
