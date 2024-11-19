#include "nRF24L01.hpp"

struct Command {
    int angle_recup;
    int power_recup;
};

// Construtor & Destructor
nRF24L01::nRF24L01(void)
{
	RF24 radio(22, 24);  // CE pin, CSN pin
	radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.setChannel(42);
    radio.openWritingPipe(this->_pipe);
    radio.stopListening();  // Mode émission
    std::cout << "nRF24L01 construtor has been called" << std::endl;
}

nRF24L01::nRF24L01(const nRF24L01 &copy) : _gpio_pin(copy._pipe)
{
	std::cout << "nRF24L01 copy constructor called" << std::endl;
}

nRF24L01 &nRF24L01::operator=(const nRF24L01 &copy)
{
	std::cout << "nRF24L01 copy assignment operator called" << std::endl;
	this->_pipe = copy._pipe;
	return (*this);
}

nRF24L01::~nRF24L01(void)
{
    std::cout << "nRF24L01 destructor has been called" << std::endl;
}


// Other Function
void nRF24L01::SendCommand(int angle, int power)
{
	Command cmd = {angle, power};
	if (radio.write(&cmd, sizeof(cmd)))
	{
        std::cout << "Commande envoyée : [" << cmd.angle_recup << ", " << cmd.power_recup << "]" << std::endl;
    } else
	{
        std::cout << "Échec de l'envoi de la commande" << std::endl;
    }
	return ;
}
