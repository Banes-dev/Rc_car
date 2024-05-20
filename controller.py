# Index of buttons for the ps4 controller : 
# croix = 0
# rond = 1
# triangle = 2
# carré = 3

# L1 = 4
# R1 = 5
# L2 = 6
# R2 = 7

# Share = 8
# Options = 9
# Ps = 10

# joystick gauche = 11
# joystick droit = 12


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
                # if event.type == pygame.JOYAXISMOTION:
                #     axis = event.axis
                #     value = event.value
                #     print(f"Axis {axis} moved to {value:.2f}")

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

                # Function for get joystick left value
                def get_left_joystick():
                    if event.type == pygame.JOYAXISMOTION:
                        axis = event.axis
                        if axis == 1:
                            value = event.value
                            print(f"Axis {axis} moved to {value:.2f}")
                            return value

    except KeyboardInterrupt:
        print("Programme interrompu par l'utilisateur.")

    finally:
        # Fermer correctement pygame
        pygame.quit()
