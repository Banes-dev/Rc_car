#include "Controller.hpp"


// Construtor & Destructor
Controller::Controller(void) : _controller(nullptr)
{
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
        std::cout << "Init issue with SDL, reason : " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Vérifier si une manette est connectée
    if (SDL_NumJoysticks() < 1)
	{
        std::cout << "No controller found ..." << std::endl;
        exit(1);
    }

    // Ouvrir la première manette
    _controller = SDL_GameControllerOpen(0);
    if (_controller == nullptr)
	{
        std::cout << "The controller cannot open, reason : " << SDL_GetError() << std::endl;
		exit(1);
    }
    std::cout << "Controller construtor has been called" << std::endl;
}

Controller::Controller(const Controller &copy) : _controller(copy._controller)
{
	std::cout << "Controller copy constructor called" << std::endl;
}

Controller &Controller::operator=(const Controller &copy)
{
	std::cout << "Controller copy assignment operator called" << std::endl;
	this->_controller = copy._controller;
	return (*this);
}

Controller::~Controller(void)
{
	if (_controller)
        SDL_GameControllerClose(_controller);
    SDL_Quit();
    std::cout << "Controller destructor has been called" << std::endl;
}


// Other Function
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

// Vérifie si la manette est connectée et prête à l'emploi
bool Controller::isConnected() const
{
    return (_controller != nullptr);
}

// Fonction pour gérer les événements de la manette
// void Controller::handleEvent(const SDL_Event& event, Servo& servo)
void Controller::handleEvent(Servo& servo)
{
    if (!isConnected())
		return ;

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_CONTROLLERAXISMOTION:
                    if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
                    {
                        std::cout << "Mouvement de l'axe gauche X : " << event.caxis.value << std::endl;
                    }
                    break;
                case SDL_CONTROLLERBUTTONDOWN:
                    std::cout << "Bouton " << (int)event.cbutton.button << " pressé." << std::endl;
                    break;
                case SDL_CONTROLLERBUTTONUP:
                    std::cout << "Bouton " << (int)event.cbutton.button << " relâché." << std::endl;
                    break;
                case SDL_QUIT:
                    std::cout << "Quit event received. Exiting..." << std::endl;
                    running = false;
                    break;
                default:
                    break;
            }
        }
        SDL_Delay(16);
    }
    // while (event.type)
    // {
    //     if ((int)event.caxis.axis == 0)
    //     {
    //         std::cout << "Mouvement de l'axe " << (int)event.caxis.axis << " : " << event.caxis.value << std::endl;
    //         // deadzone a mettre en place
    //         int new_angle = map(event.caxis.value, -3200, 3200, 207, 67);
    //         servo.MoveServo(new_angle);
    //         // break;
    //     }
    // }
    // switch (event.type)
	// {
    //     case SDL_CONTROLLERBUTTONDOWN:
    //         std::cout << "Bouton " << (int)event.cbutton.button << " pressé." << std::endl;
    //         break;
    //     case SDL_CONTROLLERBUTTONUP:
    //         std::cout << "Bouton " << (int)event.cbutton.button << " relâché." << std::endl;
    //         break;
    //     case SDL_CONTROLLERAXISMOTION:
    //         std::cout << "Mouvement de l'axe " << (int)event.caxis.axis << " : " << event.caxis.value << std::endl;
    //         break;
    //     default:
    //         break;
    // }
}

        // case SDL_CONTROLLERAXISMOTION:
        //     // if ((int)event.caxis.axis == 0)
        //     // {
        //         std::cout << "Mouvement de l'axe " << (int)event.caxis.axis << " : " << event.caxis.value << std::endl;
        //         // deadzone a mettre en place
        //         // int new_angle = map(event.caxis.value, -3200, 3200, 207, 67);
        //         // servo.MoveServo(new_angle);
        //         break;
        //     // }


                // if (event.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX) {
                //     std::cout << "Mouvement de l'axe gauche X : " << event.caxis.value << std::endl;

                //     // Gestion de la deadzone pour éviter des mouvements indésirables
                //     const int DEADZONE = 8000;
                //     if (abs(event.caxis.value) > DEADZONE) {
                //         // Remappage de la valeur de l'axe vers un angle de servo
                //         int new_angle = map(event.caxis.value, -32768, 32767, 207, 67);
                //         servo.MoveServo(new_angle);
                //     }
                // }