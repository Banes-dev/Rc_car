from gpiozero import AngularServo
from time import sleep
import pygame


# Initialiser pygame
pygame.init()
pygame.joystick.init()

def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

servo = AngularServo(18, min_pulse_width=0.0003, max_pulse_width=0.0023)


def check_manette():
    if pygame.joystick.get_count() == 0:
        print("Aucune manette détectée.")
        return None
    else:
        controller = pygame.joystick.Joystick(0)
        controller.init()
        print(f"Manette détectée : {controller.get_name()}")
        return controller

def control_servo(value):
    angle = map_value(value, -1, 1, 90, -90)
    servo.angle = angle
    print(f"Servo angle: {angle}")

def reset_servo():
    servo.angle = 0

controller = check_manette()
if controller:
    reset_servo()
    try:
        while True:
            pygame.event.pump()  # Nécessaire pour actualiser les événements Pygame
            value = controller.get_axis(0)  # Utilisation de l'axe 0 (joystick gauche, axe X)
            control_servo(value)
            sleep(0.01)
    except KeyboardInterrupt:
        print("Interruption par l'utilisateur.")
        reset_servo()
else:
    print("Connexion de la manette échouée.")
