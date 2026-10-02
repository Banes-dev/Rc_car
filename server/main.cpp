#include <chrono>
#include <thread>
#include <pigpio.h>

#include "Servo.hpp"
#include "Controller.hpp"
#include "nRF24L01.hpp"
#include "Color.hpp"


int main(int argc, char **argv)
{
    std::cout << "Test : " << argc << std::endl;
    if (argc != 2)
        return (1);

	std::string vController = argv[1];
	if (vController != "0" && vController != "1")
        return (1);

    // Init pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << Red << "Error init pigpio ..." << Reset_Color << std::endl;
        return 1;
    }

    // Init Servo & Motor
    Servo vServo(18);
    Motor vMotor(19);
    if (!vMotor.arm())
    {
        std::cerr << Red << "Erreur : Impossible d'armer le moteur." << Reset_Color << std::endl;
        gpioTerminate();
        return 1;
    }
    std::cout << Green << "ESC prêt !" << Reset_Color << std::endl;

    std::cout << Blue << " Server started " << Green << "✔" << std::endl;
    if (vController == "1")
    {
        Controller controller;
		bool running = true;
		SDL_Event event;

		// sdl loop for check event on controller
		while (running)
		{
			while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
					running = false;
                controller.HandleEvent(event, vServo, vMotor);
            }
            SDL_Delay(16);
		}
    }
    else
    {
        nRF24L01 module;

        int angle = 0;
        int power = 0;
        while (true)
        {
            module.ReceiveCommand(angle, power);
            std::cout << "Angle : " << angle << " Power : " << power << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 6ms de delai
        }
        // while(1)
        // {
            // 1e value for turn the servo
            // std::cout << "← Gauche" << std::endl;
            // vServo.MoveServo(273);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "↓ Milieux ↓" << std::endl;
            // vServo.MoveServo(137);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "→ Droite" << std::endl;
            // vServo.MoveServo(1);
            // std::this_thread::sleep_for(std::chrono::seconds(2));

            // 2e good value for turn the servo
            // std::cout << "← Gauche" << std::endl;
            // vServo.MoveServo(207);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "↓ Milieux ↓" << std::endl;
            // vServo.MoveServo(137);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
            // std::cout << "→ Droite" << std::endl;
            // vServo.MoveServo(67);
            // std::this_thread::sleep_for(std::chrono::seconds(2));
        // }
    }

    gpioTerminate();
    std::cout << Blue << "Server stopped properly." << Reset_Color << std::endl;
    return (0);
}
