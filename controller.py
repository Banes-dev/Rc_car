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
pygame.joystick.init()

def check_manette():
    if pygame.joystick.get_count() == 0:
        print("Aucune manette détectée.")
        return None
    else:
        joystick = pygame.joystick.Joystick(0)
        joystick.init()
        print(f"Manette détectée : {joystick.get_name()}")
        return joystick

def get_left_joystick_value(joystick):
    pygame.event.pump()  # Processer les événements
    axis = joystick.get_axis(1)  # Axe vertical du joystick gauche
    return axis

if __name__ == "__main__":
    joystick = check_manette()
    if joystick:
        while True:
            value = get_left_joystick_value(joystick)
            print(f"Valeur du joystick gauche : {value:.2f}")
            pygame.time.wait(10)
