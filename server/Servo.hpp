#pragma once

#include <iostream>
#include <pigpio.h>

class Servo
{
    private:
        int mGpioPin; // GPIO BCM (ex: 18)
        // Singleton
        static Servo* _instance;
        Servo(void);
    public:
        static Servo &getInstance();
        Servo(const Servo &copy);
		Servo& operator=(const Servo &copy);
        ~Servo(void);

        // Other function
        void MoveServo(int angle);
};
