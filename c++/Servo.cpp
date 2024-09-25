#include "Servo.hpp"


// Construtor & Destructor
Servo::Servo(void) : _gpio_pin(1)
{
	if (wiringPiSetup() == -1)
	{
        std::cout << "Erreur d'initialisation de wiringPi ..." << std::endl;
        exit(1);
    }
	pinMode(this->_gpio_pin, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);   // Ajuster la plage pour obtenir une précision adéquate
    pwmSetClock(192);    // Ajuster la fréquence PWM à 50Hz (192 avec range 2000 donne environ 50Hz)
    std::cout << "Servo construtor has been called" << std::endl;
}

Servo::Servo(const Servo &copy) : _gpio_pin(copy._gpio_pin)
{
	std::cout << "Servo copy constructor called" << std::endl;
}

Servo &Servo::operator=(const Servo &copy)
{
	std::cout << "Servo copy assignment operator called" << std::endl;
	this->_gpio_pin = copy._gpio_pin;
	return (*this);
}

Servo::~Servo(void)
{
	pwmWrite(this->_gpio_pin, 0);  // Stopper le signal PWM
    std::cout << "Servo destructor has been called" << std::endl;
}


// Other Function
void Servo::MoveServo(int angle)
{
	std::cout << "Debut move servo" << std::endl;
	if (angle < 0 || angle > 180)
	{
		std::cout << "The angle of servo must be between 0 and 180" << std::endl;
		return ;
	}
    // // La position du servo est définie par un signal PWM entre 500µs et 2500µs
    // // En général, les servos ont un angle de 0 à 180 degrés, ce qui correspond à une durée de 500 à 2500 microsecondes
    // int pulseWidth = (500 + (angle * 2000) / 180); // Convertit l'angle en durée d'impulsion

    // // Envoyer le signal PWM
    // pwmWrite(this->_gpio_pin, pulseWidth);


	int pulseWidth = 300 + (angle * 1900) / 180;  // 300µs (min) + la portion de 1900µs en fonction de l'angle
    int pwmValue = pulseWidth * 2000 / 2200;      // Conversion de la largeur d'impulsion en valeur PWM (0-2000)

    pwmWrite(this->_gpio_pin, pwmValue);          // Écrire le signal PWM
	std::cout << "Fin move servo" << std::endl;
	return ;
}
