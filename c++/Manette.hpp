#pragma once

#include <iostream>
#include <SDL2/SDL.h>

class Manette
{
	private:
		std::string _name;
		unsigned int _hp;
		unsigned int _energy;
		unsigned int _attack_dmg;
	public:
		Manette(std::string recup_name);
		Manette(const Manette &copy);
		Manette& operator=(const Manette &copy);
		~Manette(void);

		// Other function
		void attack(const std::string& target);
};
