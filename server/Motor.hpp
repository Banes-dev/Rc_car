#pragma once

#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <pigpio.h>

class Motor
{
    private :
        int mGpioPin;
        static constexpr int NEUTRAL_PULSE = 1500;
        static constexpr int MIN_PULSE     = 1000;
        static constexpr int MAX_PULSE     = 2000;

    public :
        // Constructor & Destructor
        explicit Motor(int aPin = 19); // GPIO BCM 19 recommended for motor
        ~Motor();

        // Other function
        void MoveMotor(int power);
        bool arm();
        void setThrottle(double throttle);
        void stop();
        void disable();
};
