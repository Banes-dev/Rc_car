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
        int _l2_value; // Etat de la gâchette gauche (frein/recul)
        int _r2_value; // Etat de la gâchette droite (accélération)

    public :
        Controller();
        Controller(const Controller &copy);
		Controller &operator=(const Controller &copy);
        ~Controller();

        // Other function
        bool IsConnected() const;
		void HandleEvent(const SDL_Event &Event, Servo &aServo, Motor &aMotor);
};
