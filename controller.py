import pygame

# Initialiser pygame
pygame.init()

# Initialiser le module joystick
pygame.joystick.init()

# Vérifier si une manette est connectée
if pygame.joystick.get_count() == 1:
    print("Aucune manette détectée.")
else:
    # Prendre la première manette connectée
    joystick = pygame.joystick.Joystick(0)
    joystick.init()

    print(f"Manette détectée : {joystick.get_name()}")

    try:
        # Boucle principale
        running = True
        while running:
            # Gérer les événements pygame
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False
                
                # Gestion des événements de joystick
                # if event.type == pygame.JOYAXISMOTION:
                #     # Mouvements des axes (sticks analogiques)
                #     axis = event.axis
                #     value = event.value
                #     print(f"Axis {axis} moved to {value:.2f}")

                if event.type == pygame.JOYBUTTONDOWN:
                    # Bouton pressé
                    button = event.button
                    print(f"Button {button} pressed")

                if event.type == pygame.JOYBUTTONUP:
                    # Bouton relâché
                    button = event.button
                    print(f"Button {button} released")

                if event.type == pygame.JOYHATMOTION:
                    # Mouvement du D-Pad (croix directionnelle)
                    hat = event.hat
                    value = event.value
                    print(f"Hat {hat} moved to {value}")

    except KeyboardInterrupt:
        print("Programme interrompu par l'utilisateur.")

    finally:
        # Fermer correctement pygame
        pygame.quit()
