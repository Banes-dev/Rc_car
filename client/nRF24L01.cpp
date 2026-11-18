#include "nRF24L01.hpp"
#include "../shared/Command.hpp"

#include <cstdlib>
#include <stdexcept>

// Variable
RF24 radio(22, 0);  // CE pin 22, CSN pin 24

// Construtor & Destructor
nRF24L01::nRF24L01(void)
{
	// radio.begin();
    if (!radio.begin())
    {
        throw std::runtime_error("Radio non initialisée correctement");
    }
    radio.setDataRate(RF24_250KBPS);
    radio.setRetries(3, 5);
    radio.setPALevel(RF24_PA_HIGH);
    radio.setChannel(42);
    radio.openWritingPipe(this->_pipe);
    radio.stopListening();  // Mode émission
    std::cout << "nRF24L01 construtor has been called" << std::endl;
}

nRF24L01::~nRF24L01(void)
{
    std::cout << "nRF24L01 destructor has been called" << std::endl;
}


// Other Function
void nRF24L01::SendCommand(int angle, int power)
{
    if (angle < 0 || angle > 180 || power < -100 || power > 100)
        return;

	Command cmd = {static_cast<std::int16_t>(angle),
	               static_cast<std::int16_t>(power)};
	if (radio.write(&cmd, sizeof(cmd)))
	{
        std::cout << "Commande envoyée : [" << cmd.angle << ", " << cmd.throttle << "]" << std::endl;
    } else
	{
        std::cout << "Échec de l'envoi de la commande" << std::endl;
    }
	return ;
}
