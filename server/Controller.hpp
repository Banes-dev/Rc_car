#pragma once

#include <iostream>
#include <cmath>
#include "SDL2/SDL.h"

#include "Servo.hpp"
#include "Motor.hpp"

class Controller
{
    private :
        SDL_GameController *mController;
        SDL_Joystick *mJoystick;
        int mL2Value; // Etat de la gâchette gauche (frein/recul)
        int mR2Value; // Etat de la gâchette droite (accélération)

    public :
        Controller();
        ~Controller();

        // Other function
        bool IsConnected() const;
		void HandleEvent(const SDL_Event &aEvent, Servo &aServo, Motor &aMotor);
        void Update(Servo &aServo, Motor &aMotor);
};
