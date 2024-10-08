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
// Vérifie si la manette est connectée et prête à l'emploi
bool Controller::isConnected() const
{
    return (_controller != nullptr);
}

// Fonction pour gérer les événements de la manette
void Controller::handleEvent(const SDL_Event& event)
{
    if (!isConnected())
		return ;
    switch (event.type)
	{
        case SDL_CONTROLLERBUTTONDOWN:
            std::cout << "Bouton " << (int)event.cbutton.button << " pressé." << std::endl;
            break;
        case SDL_CONTROLLERBUTTONUP:
            std::cout << "Bouton " << (int)event.cbutton.button << " relâché." << std::endl;
            break;
        case SDL_CONTROLLERAXISMOTION:
            std::cout << "Mouvement de l'axe " << (int)event.caxis.axis << " : " << event.caxis.value << std::endl;
            break;
        default:
            break;
    }
}
