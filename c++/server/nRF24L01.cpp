#include "nRF24L01.hpp"


// Variable
RF24 radio(22, 24);  // CE pin 22, CSN pin 24

struct Command {
    int angle_recup;
    int power_recup;
};


// Construtor & Destructor
nRF24L01::nRF24L01(void)
{
	if (!radio.begin())
    {
        std::cerr << "Erreur : radio non initialisée correctement !" << std::endl;
        exit(EXIT_FAILURE);
    }
    radio.setPALevel(RF24_PA_HIGH);
    radio.setChannel(42);
    radio.openReadingPipe(1, this->_pipe);
    radio.startListening();  // Mode réception
    std::cout << "nRF24L01 construtor has been called" << std::endl;
}

// nRF24L01::nRF24L01(const nRF24L01 &copy)
// {
// 	std::cout << "nRF24L01 copy constructor called" << std::endl;
// }

// nRF24L01 &nRF24L01::operator=(const nRF24L01 &copy)
// {
// 	std::cout << "nRF24L01 copy assignment operator called" << std::endl;
// 	return (*this);
// }

nRF24L01::~nRF24L01(void)
{
    std::cout << "nRF24L01 destructor has been called" << std::endl;
}


// Other Function
void nRF24L01::ReceiveCommand(int &angle, int &power)
{
    if (radio.available())
    {
        Command cmd;
        radio.read(&cmd, sizeof(cmd)); 
        std::cout << "Commande reçue : [" << cmd.angle_recup << ", " << cmd.power_recup << "]" << std::endl;
        angle = cmd.angle_recup;
        power = cmd.power_recup;
    }
    else
    {
        angle = -1;
        power = -1;
    }
	return ;
}
