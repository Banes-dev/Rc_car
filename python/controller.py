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
pygame.controller.init()

def check_manette():
    if pygame.controller.get_count() == 0:
        print("Aucune manette détectée.")
        return None
    else:
        controller = pygame.controller.Joystick(0)
        controller.init()
        print(f"Manette détectée : {controller.get_name()}")
        return controller

def get_left_joystick_value(controller):
    pygame.event.pump()  # Processer les événements
    axis = controller.get_axis(1)  # Axe vertical du joystick gauche
    return axis

if __name__ == "__main__":
    controller = check_manette()
    if controller:
        while True:
            value = get_left_joystick_value(controller)
            print(f"Valeur du joystick gauche : {value:.2f}")
            pygame.time.wait(100)
