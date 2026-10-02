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

    gpioServo(mGpioPin, NEUTRAL_PULSE);
    sleep(2); // Laisse l'ESC s'initialiser
    return true;
}

void Motor::setThrottle(double throttle)
{
    throttle = std::clamp(throttle, -1.0, 1.0);

    int pulse = NEUTRAL_PULSE;
    if (throttle > 0.0) {
        pulse = NEUTRAL_PULSE + static_cast<int>(throttle * (MAX_PULSE - NEUTRAL_PULSE));
    } else if (throttle < 0.0) {
        pulse = NEUTRAL_PULSE + static_cast<int>(throttle * (NEUTRAL_PULSE - MIN_PULSE));
    }

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
