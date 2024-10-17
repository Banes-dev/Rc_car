#pragma once

#include "iostream" 
#include "Servo.hpp"
#include "SDL2/SDL.h"

class Controller
{
    private:
        SDL_GameController* _controller;
    public:
        Controller(void);
        Controller(const Controller &copy);
		Controller& operator=(const Controller &copy);
        ~Controller(void);

        // Other function
        bool isConnected() const;
		void handleEvent(const SDL_Event& event, Servo servo);
};
