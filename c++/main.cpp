#include "Manette.hpp"

// Fonction qui affiche quel bouton est appuyé
void printButtonPressed(SDL_Event& event)
{
    if (event.type == SDL_JOYBUTTONDOWN)
        std::cout << "Button pressed : " << (int)event.jbutton.button << std::endl;
    else if (event.type == SDL_JOYAXISMOTION)
	{
        // Les sticks analogiques et les gâchettes sont des axes
        std::cout << "Axis moved : " << (int)event.jaxis.axis << " Value : " << event.jaxis.value << std::endl;
    }
}

int main()
{
    // Initialiser SDL avec la gestion des manettes
    if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC) < 0)
	{
        std::cerr << "Impossible d'initialiser SDL : " << SDL_GetError() << std::endl;
        return (-1);
    }

    // Vérifier si une manette est branchée
    if (SDL_NumJoysticks() < 1)
	{
        std::cerr << "Aucune manette connectée !" << std::endl;
        SDL_Quit();
        return (-1);
    }

    // Ouvrir la première manette (index 0)
    SDL_Joystick* joystick = SDL_JoystickOpen(0);
    if (joystick == nullptr)
	{
        std::cerr << "Impossible d'ouvrir la manette : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return (-1);
    }
    std::cout << "Manette détectée : " << SDL_JoystickName(joystick) << std::endl;

    SDL_Event event;
    bool quit = false;

    // Boucle principale pour capturer les événements
    while (!quit)
	{
        // Regarder les événements SDL
        while (SDL_PollEvent(&event) != 0) {
            // Si on ferme la fenêtre ou appuie sur Échap, on quitte
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_JOYBUTTONDOWN || event.type == SDL_JOYAXISMOTION) {
                // Si un bouton ou un axe de la manette est utilisé
                printButtonPressed(event);
            }
        }
    }

    // Fermer la manette
    SDL_JoystickClose(joystick);
    joystick = nullptr;

    // Quitter SDL proprement
    SDL_Quit();
    return (0);
}