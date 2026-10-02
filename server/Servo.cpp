#include "Servo.hpp"


// Constructor & Destructor
Servo::Servo(int aPin) : mGpioPin(aPin)
{
    gpioSetMode(this->mGpioPin, PI_OUTPUT);
    std::cout << "Servo constructor has been called" << std::endl;
}
Servo::Servo(const Servo &copy) : mGpioPin(copy.mGpioPin)
{
    std::cout << "Servo copy constructor called" << std::endl;
}
Servo &Servo::operator=(const Servo &copy)
{
    std::cout << "Servo copy assignment operator called" << std::endl;
    if (this != &copy)
        this->mGpioPin = copy.mGpioPin;
    return (*this);
}
Servo::~Servo(void)
{
    gpioServo(this->mGpioPin, 0);
    std::cout << "Servo destructor has been called" << std::endl;
}

// Other function
void Servo::MoveServo(const int angle)
{
    // std::cout << "Debut move servo" << std::endl;

    if (angle < 0 || angle > 180)
    {
        std::cerr << "Angle must be between 0 and 180" << std::endl;
        return;
    }

    // Conversion angle -> pulse width (µs)
	const int minPulse = 500;
	const int maxPulse = 2250;
	int pulseWidth = minPulse + (angle * (maxPulse - minPulse)) / 180;

    gpioServo(this->mGpioPin, pulseWidth);

    // std::cout << "Pulse width : " << pulseWidth << " us" << std::endl;
    // std::cout << "Fin move servo" << std::endl;
}
