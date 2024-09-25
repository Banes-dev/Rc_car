#pragma once

#include "iostream"
#include "wiringPi.h"

class Servo
{
    private:
        int _gpio_pin;
    public:
        Servo(void);
        Servo(const Servo &copy);
		Servo& operator=(const Servo &copy);
        ~Servo(void);

        // Other function
        void MoveServo(int angle);
};
