#include "Motor.hpp"

#include <cmath>
#include <stdexcept>

// Constructor & Destructor
Motor::Motor(int aPin) : mGpioPin(aPin)
{
    std::cout << "Motor constructor called on pin " << mGpioPin << std::endl;
}

Motor::~Motor()
{
    Stop();
    Disable();
    std::cout << "Motor destructor called" << std::endl;
}

// Other function
bool Motor::Arm()
{
    if (gpioSetMode(mGpioPin, PI_OUTPUT) != 0)
        throw std::runtime_error("Unable to configure motor GPIO pin");
    if (gpioServo(mGpioPin, NEUTRAL_PULSE) < 0)
        return false;
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Let the ESC arm for 2 seconds
    return true;
}

void Motor::SetThrottle(double aThrottle)
{
    if (!std::isfinite(aThrottle))
        throw std::invalid_argument("Motor throttle must be a finite value");

    aThrottle = std::max(-1.0, std::min(aThrottle, 1.0));

    int pulse = NEUTRAL_PULSE;
    if (aThrottle > 0.0)
        pulse = NEUTRAL_PULSE + static_cast<int>(aThrottle * (MAX_PULSE - NEUTRAL_PULSE));
    else if (aThrottle < 0.0)
        pulse = NEUTRAL_PULSE + static_cast<int>(aThrottle * (NEUTRAL_PULSE - MIN_PULSE));

    if (gpioServo(mGpioPin, pulse) < 0)
        throw std::runtime_error("Unable to send motor PWM command");
}

void Motor::Stop()
{
    gpioServo(mGpioPin, NEUTRAL_PULSE);
}

void Motor::Disable()
{
    gpioServo(mGpioPin, 0);
}
