#include "iostream"
#include "chrono"
#include "thread"

#include "Servo.hpp"
#include "Controller.hpp"


int main(int argc, char **argv)
{
    std::cout << "Test : " << argc << std::endl;
    if (argc != 2)
        return (1);
	std::string new_argv1 = argv[1];
	if (new_argv1 != "0" && new_argv1 != "1")
        return (1);
    Servo servo;

    std::cout << "Rc Car started ✔" << std::endl;
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
        while(1)
        {
            // std::cout << "← Gauche" << std::endl;
            // servo.MoveServo(273);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "↓ Milieux ↓" << std::endl;
            // servo.MoveServo(137);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "→ Droite" << std::endl;
            // servo.MoveServo(1);
            // std::this_thread::sleep_for(std::chrono::seconds(2));

            std::cout << "← Gauche" << std::endl;
            servo.MoveServo(207);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "↓ Milieux ↓" << std::endl;
            servo.MoveServo(137);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "→ Droite" << std::endl;
            servo.MoveServo(67);
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
    return (0);
}
