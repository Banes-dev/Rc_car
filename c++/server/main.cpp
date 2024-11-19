#include <iostream>
#include <chrono>
#include <thread>

#include "Servo.hpp"
#include "Controller.hpp"
#include "nRF24L01.hpp"


int main(int argc, char **argv)
{
    std::cout << "Test : " << argc << std::endl;
    if (argc != 2)
    {
        return (1);  
    }
	std::string new_argv1 = argv[1];
	if (new_argv1 != "0" && new_argv1 != "1")
        return (1);
    Servo servo;
    nRF24L01 module;

    std::cout << Blue << " Server started " << Green << "✔" << std::endl;
    if (new_argv1 == "1")
    {
        Controller controller;

		// code avec la manette
		bool running = true;
		SDL_Event event;

		// Boucle de gestion des événements
		while (running)
		{
			while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
					running = false;
                controller.handleEvent(event, servo);
            }
            SDL_Delay(16);
		}
    }
    else
    {
        int angle = 0;
        int power = 0;
        while (true)
        {
            angle, power = module.ReceiveCommand(angle, power);
            std::cout << "Angle : " << angle << " Power : " << power << std::endl;
        }
        // while(1)
        // {
            // 1e value for turn the servo
            // std::cout << "← Gauche" << std::endl;
            // servo.MoveServo(273);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "↓ Milieux ↓" << std::endl;
            // servo.MoveServo(137);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "→ Droite" << std::endl;
            // servo.MoveServo(1);
            // std::this_thread::sleep_for(std::chrono::seconds(2));

            // 2e good value for turn the servo
            // std::cout << "← Gauche" << std::endl;
            // servo.MoveServo(207);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "↓ Milieux ↓" << std::endl;
            // servo.MoveServo(137);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "→ Droite" << std::endl;
            // servo.MoveServo(67);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
        // }
    }
    return (0);
}
