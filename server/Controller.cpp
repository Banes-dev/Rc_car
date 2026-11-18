#include "Controller.hpp"

#include <algorithm>
#include <string>
#include <stdexcept>

// Construtor & Destructor
Controller::Controller(void) : mController(nullptr), mJoystick(nullptr), mL2Value(0), mR2Value(0)
{
    // Init SDL2 for controller
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0)
	{
        throw std::runtime_error(std::string("Unable to initialize SDL: ") + SDL_GetError());
    }

    // Check if any controller is connected
    if (SDL_NumJoysticks() < 1)
	{
        SDL_Quit();
        throw std::runtime_error("No controller found");
    }

    // Open the first GameController found. Some devices are exposed only as
    // regular joysticks, so keep a fallback for them.
    for (int i = 0; i < SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            mController = SDL_GameControllerOpen(i);
            if (mController)
                break;
        }
    }

    if (mController == nullptr)
    {
        for (int i = 0; i < SDL_NumJoysticks(); ++i)
        {
            mJoystick = SDL_JoystickOpen(i);
            if (mJoystick)
                break;
        }
    }

    if (mController == nullptr && mJoystick == nullptr)
	{
        SDL_Quit();
        throw std::runtime_error(std::string("Unable to open controller: ") + SDL_GetError());
    }
    std::cout << "Controller construtor has been called" << std::endl;
}

Controller::~Controller(void)
{
	if (mController)
        SDL_GameControllerClose(mController);
    if (mJoystick)
        SDL_JoystickClose(mJoystick);
    SDL_Quit();
    std::cout << "Controller destructor has been called" << std::endl;
}


// Other Function
static int Map(int x, int in_min, int in_max, int out_min, int out_max)
{
    return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

bool Controller::IsConnected() const
{
    return (mController != nullptr || mJoystick != nullptr);
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

    if (aEvent.type == SDL_CONTROLLERDEVICEREMOVED)
    {
        aServo.MoveServo(90);
        aMotor.Stop();
        return;
    }

    if (aEvent.type == SDL_JOYDEVICEREMOVED)
    {
        aServo.MoveServo(90);
        aMotor.Stop();
        return;
    }

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
                int new_angle = Map(aEvent.caxis.value, -32768, 32767, 180, 0);
                aServo.MoveServo(new_angle);
            }
            else
                aServo.MoveServo(90); // put in the middle
        }
        // Handle L2
        else if (aEvent.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
            mL2Value = aEvent.caxis.value; // de 0 à 32767
        
        // Handle R2
        else if (aEvent.caxis.axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
            mR2Value = aEvent.caxis.value; // de 0 à 32767


        // On calcule la vitesse (Throttle) à chaque mouvement d'axe
        // R2 pousse vers 1.0 (avant), L2 pousse vers -1.0 (arrière)
        double accel = static_cast<double>(std::max(0, mR2Value)) / 32767.0;
        double brake = static_cast<double>(std::max(0, mL2Value)) / 32767.0;
        double throttle = accel - brake; 

        aMotor.SetThrottle(throttle);
    }
    else if (aEvent.type == SDL_JOYAXISMOTION)
    {
        // Generic joystick fallback. Axis 0 is normally steering/left X,
        // axes 2 and 5 are commonly used by L2/R2 on gamepads.
        if (aEvent.jaxis.axis == 0)
        {
            const int DEADZONE = 4000;
            if (std::abs(aEvent.jaxis.value) > DEADZONE)
            {
                int new_angle = Map(aEvent.jaxis.value, -32768, 32767, 180, 0);
                aServo.MoveServo(new_angle);
            }
            else
                aServo.MoveServo(90);
        }
        else if (aEvent.jaxis.axis == 2)
            mL2Value = std::max(0, aEvent.jaxis.value);
        else if (aEvent.jaxis.axis == 5)
            mR2Value = std::max(0, aEvent.jaxis.value);

        double throttle = static_cast<double>(mR2Value) / 32767.0
                        - static_cast<double>(mL2Value) / 32767.0;
        aMotor.SetThrottle(throttle);
    }
}

void Controller::Update(Servo &aServo, Motor &aMotor)
{
    if (!IsConnected())
        return;

    if (mController)
    {
        int leftX = SDL_GameControllerGetAxis(mController, SDL_CONTROLLER_AXIS_LEFTX);
        int leftTrigger = SDL_GameControllerGetAxis(mController, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
        int rightTrigger = SDL_GameControllerGetAxis(mController, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

        mL2Value = leftTrigger;
        mR2Value = rightTrigger;

        const int DEADZONE = 4000;
        if (std::abs(leftX) > DEADZONE)
            aServo.MoveServo(Map(leftX, -32768, 32767, 180, 0));
        else
            aServo.MoveServo(90);

        int normalizedLeft = std::max(0, mL2Value);
        int normalizedRight = std::max(0, mR2Value);
        double throttle = static_cast<double>(normalizedRight) / 32767.0
                        - static_cast<double>(normalizedLeft) / 32767.0;
        aMotor.SetThrottle(throttle);
    }
    else
    {
        int leftX = SDL_JoystickGetAxis(mJoystick, 0);
        int leftTrigger = SDL_JoystickGetAxis(mJoystick, 2);
        int rightTrigger = SDL_JoystickGetAxis(mJoystick, 5);

        mL2Value = std::max(0, leftTrigger);
        mR2Value = std::max(0, rightTrigger);

        const int DEADZONE = 4000;
        if (std::abs(leftX) > DEADZONE)
            aServo.MoveServo(Map(leftX, -32768, 32767, 180, 0));
        else
            aServo.MoveServo(90);

        double throttle = static_cast<double>(mR2Value) / 32767.0
                        - static_cast<double>(mL2Value) / 32767.0;
        aMotor.SetThrottle(throttle);
    }
}
