#include "nRF24L01.hpp"
#include "../shared/Command.hpp"

#include <stdexcept>

// Variable
RF24 radio(22, 0);  // CE pin 22, CSN pin 24

// Construtor & Destructor
nRF24L01::nRF24L01(void)
{
	if (!radio.begin())
    {
        throw std::runtime_error("Radio non initialisée correctement");
    }
    radio.setDataRate(RF24_250KBPS);
    radio.setRetries(3, 5);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setChannel(42);
    radio.openReadingPipe(1, this->_pipe);
    radio.startListening();  // Mode réception
    std::cout << "nRF24L01 construtor has been called" << std::endl;
}

nRF24L01::~nRF24L01(void)
{
    std::cout << "nRF24L01 destructor has been called" << std::endl;
}


// Other Function
bool nRF24L01::ReceiveCommand(int &angle, int &power)
{
    if (radio.available())
    {
        Command cmd;
        radio.read(&cmd, sizeof(cmd)); 
        if (cmd.angle < 0 || cmd.angle > 180 ||
            cmd.throttle < -100 || cmd.throttle > 100)
            return false;

        angle = cmd.angle;
        power = cmd.throttle;
        return true;
    }
    return false;
}
