#include <chrono>
#include <thread>
#include <csignal>
#include <exception>
#include <stdexcept>
#include <string>
#include <pigpio.h>

#include "Color.hpp"
#include "Servo.hpp"
#include "Controller.hpp"
#include "nRF24L01.hpp"


static volatile std::sig_atomic_t gRunning = 1;

static void HandleShutdownSignal(int)
{
    gRunning = 0;
}

int main(int argc, char **argv)
{
    bool vPigpioInitialized = false;
    std::signal(SIGINT, HandleShutdownSignal);
    std::signal(SIGTERM, HandleShutdownSignal);

    try
    {
        if (argc != 2)
            throw std::invalid_argument("Usage : ./Server <0|1>");

        std::string vMode = argv[1];
        if (vMode != "0" && vMode != "1")
            throw std::invalid_argument("Mode must be 0 (RF24) or 1 (SDL controller)");

        if (gpioInitialise() < 0)
            throw std::runtime_error("Unable to initialize pigpio");

        vPigpioInitialized = true;

        Servo vServo(18);
        Motor vMotor(19);
        vServo.MoveServo(90);

        if (!vMotor.Arm())
            throw std::runtime_error("Unable to arm motor ESC");

        std::cout << Green << "ESC ready" << Valid << Reset_Color << std::endl;
        std::cout << Blue << "Server started" << Valid << Reset_Color << std::endl;

        if (vMode == "1")
        {
            Controller vController;
            SDL_Event vEvent;
            auto vLastControllerEvent = std::chrono::steady_clock::now();

            while (gRunning)
            {
                while (SDL_PollEvent(&vEvent))
                {
                    if (vEvent.type == SDL_QUIT)
                        gRunning = 0;
                    else
                    {
                        vController.HandleEvent(vEvent, vServo, vMotor);
                        if (vEvent.type == SDL_CONTROLLERAXISMOTION || vEvent.type == SDL_CONTROLLERDEVICEREMOVED)
                            vLastControllerEvent = std::chrono::steady_clock::now();
                    }
                }

                if (std::chrono::steady_clock::now() - vLastControllerEvent > std::chrono::milliseconds(500))
                {
                    vServo.MoveServo(90);
                    vMotor.Stop();
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

            while (gRunning)
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
                vMotor.SetThrottle(static_cast<double>(vPower) / 100.0);
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
    catch (const std::exception &aError)
    {
        std::cerr << Deny << Red << aError.what() << Reset_Color << std::endl;
        if (vPigpioInitialized)
            gpioTerminate();
        return 1;
    }

    if (vPigpioInitialized)
        gpioTerminate();
    std::cout << Blue << "Server stopped properly" << Reset_Color << std::endl;
    return 0;
}
