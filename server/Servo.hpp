#pragma once

#include <iostream>
#include <pigpio.h>

class Servo
{
    private :
        int mGpioPin; // GPIO BCM (ex: 18)

    public :
        // Constructor & Destructor
        explicit Servo (int aPin = 18); // GPIO BCM 18 recommended for servo
        Servo(const Servo &copy);
		Servo& operator=(const Servo &copy);
        ~Servo(void);

        // Other function
        void MoveServo(const int angle);
};
