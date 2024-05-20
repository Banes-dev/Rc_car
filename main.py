import controller 
import servo
from servo import reset_servo

try:
    reset_servo()
    # # Boucle principale
    # running = True
    # while running:
    #     # Gérer les événements pygame
    #     for event in pygame.event.get():
    #         if event.type == pygame.QUIT:
    #             running = False
            
    #         # Mouvements des axes (sticks analogiques)
    #         # if event.type == pygame.JOYAXISMOTION:
    #         #     axis = event.axis
    #         #     value = event.value
    #         #     print(f"Axis {axis} moved to {value:.2f}")
    #          # Bouton pressé
    #         if event.type == pygame.JOYBUTTONDOWN:
    #             button = event.button
    #             print(f"Button {button} pressed")
    #         # Bouton relâché
    #         # if event.type == pygame.JOYBUTTONUP:
    #         #     button = event.button
    #         #     print(f"Button {button} released")
    #         # Mouvement du D-Pad (croix directionnelle)
    #         if event.type == pygame.JOYHATMOTION:
    #             hat = event.hat
    #             value = event.value
    #             print(f"Hat {hat} moved to {value}")
except KeyboardInterrupt:
    reset_servo()
    print("Programme interrompu par l'utilisateur.")
finally:
    # Fermer correctement
    print("Program as quit.")