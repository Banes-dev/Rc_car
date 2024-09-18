#include "Manette.hpp"

// Construtor etc
Manette::Manette(std::string recup_name) : _name(recup_name), _hp(10), _energy(10), _attack_dmg(0)
{
	std::cout << "Manette " << recup_name << " constructor called" << std::endl;
}

Manette::Manette(const Manette &copy) : _name(copy._name), _hp(copy._hp), _energy(copy._energy), _attack_dmg(copy._attack_dmg)
{
	std::cout << "Copy constructor called" << std::endl;
}

Manette &Manette::operator=(const Manette &copy)
{
	std::cout << "Copy assignment operator called" << std::endl;
	this->_name = copy._name;
	this->_hp = copy._hp;
	this->_energy = copy._energy;
	this->_attack_dmg = copy._attack_dmg;
	return (*this);
}

Manette::~Manette(void)
{
	std::cout << "Manette " << this->_name << " Destructor called" << std::endl;
}

// Other function
void Manette::attack(const std::string& target)
{
	if (this->_hp > 0 && this->_energy > 0)
	{
		std::cout << "Manette " << this->_name << " attacks " << target << ", causing " << this->_attack_dmg << " points of damage !" << std::endl;
		this->_energy = this->_energy - 1;
	}
	else
		std::cout << "Manette " << this->_name << " has not enought hp or energy for attack" << std::endl;
}
