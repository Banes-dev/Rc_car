#include "Servo.hpp"


Servo *Servo::_instance = nullptr;
Servo &Servo::getInstance()
{
    if (!_instance)
        _instance = new Servo();
    return *_instance;
}

// Constructor & Destructor
Servo::Servo(void) : mGpioPin(18) // GPIO BCM 18 recommandé pour servo
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "Error init pigpio ..." << std::endl;
        exit(1);
    }

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
    this->mGpioPin = copy.mGpioPin;
    return (*this);
}
Servo::~Servo(void)
{
    gpioServo(this->mGpioPin, 0);
    gpioTerminate();
    std::cout << "Servo destructor has been called" << std::endl;
}

// Move servo
void Servo::MoveServo(int angle)
{
    std::cout << "Debut move servo" << std::endl;

    if (angle < 0 || angle > 180)
    {
        std::cerr << "Angle must be between 0 and 180" << std::endl;
        return;
    }

    // Conversion angle -> pulse width (µs)
	int minPulse = 500;
	int maxPulse = 2500;
	int pulseWidth = minPulse + (angle * (maxPulse - minPulse)) / 180;
    // int pulseWidth = 500 + (angle * 2000) / 180; // 500–2500 µs
	// int pulseWidth = 1000 + (angle * 1000) / 180;

    gpioServo(this->mGpioPin, pulseWidth);

    std::cout << "Pulse width: " << pulseWidth << " us" << std::endl;
    std::cout << "Fin move servo" << std::endl;
}
