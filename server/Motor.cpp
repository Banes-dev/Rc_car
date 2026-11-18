#include "Motor.hpp"


// Constructor & Destructor
Motor::Motor(int aPin) : mGpioPin(aPin)
{
    std::cout << "Motor constructor called on pin " << mGpioPin << std::endl;
}

Motor::~Motor()
{
    stop();
    disable();
    std::cout << "Motor destructor called" << std::endl;
}

// Other function
bool Motor::arm()
{
    if (gpioSetMode(mGpioPin, PI_OUTPUT) != 0)
        return false;

    if (gpioServo(mGpioPin, NEUTRAL_PULSE) < 0)
        return false;
    sleep(2); // Let the ESC arm for 2 seconds
    return true;
}

void Motor::setThrottle(double aThrottle)
{
    aThrottle = std::max(-1.0, std::min(aThrottle, 1.0));

    int pulse = NEUTRAL_PULSE;
    if (aThrottle > 0.0)
        pulse = NEUTRAL_PULSE + static_cast<int>(aThrottle * (MAX_PULSE - NEUTRAL_PULSE));
    else if (aThrottle < 0.0)
        pulse = NEUTRAL_PULSE + static_cast<int>(aThrottle * (NEUTRAL_PULSE - MIN_PULSE));

    gpioServo(mGpioPin, pulse);
}

void Motor::stop()
{
    gpioServo(mGpioPin, NEUTRAL_PULSE);
}

void Motor::disable()
{
    gpioServo(mGpioPin, 0);
}
