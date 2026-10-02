#include "Controller.hpp"


// Construtor & Destructor
Controller::Controller(void) : mController(nullptr)
{
    // Init SDL2 for controller
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
        std::cout << "Init issue with SDL, reason : " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Check if any controller is connected
    if (SDL_NumJoysticks() < 1)
	{
        std::cout << "No controller found ..." << std::endl;
        exit(1);
    }

    // Open the first available controller
    mController = SDL_GameControllerOpen(0);
    if (mController == nullptr)
	{
        std::cout << "The controller cannot open, reason : " << SDL_GetError() << std::endl;
		exit(1);
    }
    std::cout << "Controller construtor has been called" << std::endl;
}

Controller::Controller(const Controller &copy) : mController(copy.mController)
{
	std::cout << "Controller copy constructor called" << std::endl;
}

Controller &Controller::operator=(const Controller &copy)
{
	std::cout << "Controller copy assignment operator called" << std::endl;
	this->mController = copy.mController;
	return (*this);
}

Controller::~Controller(void)
{
	if (mController)
        SDL_GameControllerClose(mController);
    SDL_Quit();
    std::cout << "Controller destructor has been called" << std::endl;
}


// Other Function
int map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

bool Controller::IsConnected() const
{
    return (mController != nullptr);
}

void Controller::HandleEvent(const SDL_Event &aEvent, Servo &aServo, Motor &aMotor)
{
    if (!IsConnected())
		return ;

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

    if (aEvent.type == SDL_CONTROLLERAXISMOTION)
    {
        // Handle left stick X-axis
        if (aEvent.caxis.axis == SDL_CONTROLLER_AXIS_LEFTX)
        {
            // std::cout << "Mouvement of left axis X : " << aEvent.caxis.value << std::endl;

            // deadzone value for movement
            const int DEADZONE = 4000; // 8000
            if (std::abs(aEvent.caxis.value) > DEADZONE)
            {
                // remap stick value to servo value
                int new_angle = map(aEvent.caxis.value, -32768, 32767, 180, 0);
                aServo.MoveServo(new_angle);
            }
            else
                aServo.MoveServo(90); // put in the middle
        }
        // Handle L2
        else if (aEvent.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
            _l2_value = aEvent.caxis.value; // de 0 à 32767
        
        // Handle R2
        else if (aEvent.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
            _r2_value = aEvent.caxis.value; // de 0 à 32767


        // On calcule la vitesse (Throttle) à chaque mouvement d'axe
        // R2 pousse vers 1.0 (avant), L2 pousse vers -1.0 (arrière)
        double accel = static_cast<double>(_r2_value) / 32767.0;
        double brake = static_cast<double>(_l2_value) / 32767.0;
        double throttle = accel - brake; 

        aMotor.setThrottle(throttle);
    }
}
