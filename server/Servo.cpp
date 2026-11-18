#include "Servo.hpp"

#include <stdexcept>

// Constructor & Destructor
Servo::Servo(int aPin) : mGpioPin(aPin)
{
    if (gpioSetMode(this->mGpioPin, PI_OUTPUT) != 0)
        throw std::runtime_error("Unable to configure servo GPIO pin");
    std::cout << "Servo constructor has been called" << std::endl;
}
Servo::~Servo()
{
    disable();
    std::cout << "Servo destructor has been called" << std::endl;
}

// Other function
void Servo::MoveServo(const int aAngle)
{
    // std::cout << "Debut move servo" << std::endl;

    if (aAngle < 0 || aAngle > 180)
        throw std::invalid_argument("Servo angle must be between 0 and 180");

    // Conversion angle -> pulse width (µs)
	const int minPulse = 500;
	const int maxPulse = 2250;
	int pulseWidth = minPulse + (aAngle * (maxPulse - minPulse)) / 180;

    if (gpioServo(this->mGpioPin, pulseWidth) < 0)
        throw std::runtime_error("Unable to send servo PWM command");
}

void Servo::disable()
{
    gpioServo(this->mGpioPin, 0);
}
