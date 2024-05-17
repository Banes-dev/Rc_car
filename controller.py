import pygame

# Initialiser pygame
pygame.init()

# Initialiser le module joystick
pygame.joystick.init()

# Vérifier si une manette est connectée
if pygame.joystick.get_count() == 0:
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
                
                # Mouvements des axes (sticks analogiques)
                if event.type == pygame.JOYAXISMOTION:
                    axis = event.axis
                    value = event.value
                    print(f"Axis {axis} moved to {value:.2f}")

                 # Bouton pressé
                if event.type == pygame.JOYBUTTONDOWN:
                    button = event.button
                    print(f"Button {button} pressed")

                # Bouton relâché
                # if event.type == pygame.JOYBUTTONUP:
                #     button = event.button
                #     print(f"Button {button} released")

                # Mouvement du D-Pad (croix directionnelle)
                if event.type == pygame.JOYHATMOTION:
                    hat = event.hat
                    value = event.value
                    print(f"Hat {hat} moved to {value}")

    except KeyboardInterrupt:
        print("Programme interrompu par l'utilisateur.")

    finally:
        # Fermer correctement pygame
        pygame.quit()
