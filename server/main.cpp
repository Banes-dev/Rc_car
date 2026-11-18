#include <chrono>
#include <thread>
#include <pigpio.h>

#include "Color.hpp"
#include "Servo.hpp"
#include "Controller.hpp"
#include "nRF24L01.hpp"


int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;

	std::string vMode = argv[1];
	if (vMode != "0" && vMode != "1")
        return 1;

    // Init pigpio
    if (gpioInitialise() < 0)
    {
        std::cerr << Deny << Red << "Error init pigpio" << Reset_Color << std::endl;
        return 1;
    }

    // Init Servo & Motor
    {
    Servo vServo(18);
    Motor vMotor(19);
    vServo.MoveServo(90);
    if (!vMotor.arm())
    {
        std::cerr << Deny << Red << "Error init Motor" << Reset_Color << std::endl;
        vServo.MoveServo(90);
        vMotor.disable();
        return 1;
    }
    std::cout << Green << "ESC ready" << Valid << Reset_Color << std::endl;

    std::cout << Blue << " Server started " << Valid << std::endl;
    if (vMode == "1")
    {
        Controller vController;
        SDL_Event vEvent;
		bool vRunning = true;

		// SDL loop for check event on controller
		while (vRunning)
		{
			while (SDL_PollEvent(&vEvent))
            {
                if (vEvent.type == SDL_QUIT)
					vRunning = false;
                vController.HandleEvent(vEvent, vServo, vMotor);
            }
            SDL_Delay(16);
		}
    }
    else
    {
        nRF24L01 vModule;

        int vAngle = 90;
        int vPower = 0;
        auto vLastCommand = std::chrono::steady_clock::now();
        while (true)
        {
            if (vModule.ReceiveCommand(vAngle, vPower))
                vLastCommand = std::chrono::steady_clock::now();

            const auto elapsed = std::chrono::steady_clock::now() - vLastCommand;
            if (elapsed > std::chrono::milliseconds(500))
            {
                vAngle = 90;
                vPower = 0;
            }

            vServo.MoveServo(vAngle);
            vMotor.setThrottle(static_cast<double>(vPower) / 100.0);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
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
    }

    gpioTerminate();
    std::cout << Blue << "Server stopped properly" << Reset_Color << std::endl;
    return 0;
}
