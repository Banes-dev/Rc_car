from gpiozero import AngularServo
from time import sleep
# import controller

import pygame

# Initialiser pygame
pygame.init()
pygame.joystick.init()


def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

servo = AngularServo(18, min_pulse_width=0.0003, max_pulse_width=0.0023)


def check_manette():
    if pygame.controller.get_count() == 0:
        print("Aucune manette détectée.")
        return None
    else:
        controller = pygame.controller.Joystick(0)
        controller.init()
        print(f"Manette détectée : {controller.get_name()}")
        return controller

def control_servo(value):
    angle_test = map_value(value, -1, 1, -90, 90)
    servo.angle = angle_test
    print(f"Servo angle: {angle_test}")
    # servo.angle = 0
    # sleep(2)
    # servo.angle = 90
    # sleep(2)
    # servo.angle = 0
    # sleep(2)
    # servo.angle = -90
    # sleep(2)
    # servo.angle = 0
    # sleep(2)

def reset_servo():
    servo.angle = 0
    value = controller.get_left_joystick_value(joystick)
    control_servo(value)

check_manette()
while controller != NULL:
    reset_servo()

# if __name__ == "__main__":
#     # joystick = controller.check_manette()
#     # if joystick:
#         while True:
#             # value = controller.get_left_joystick_value(joystick)
#             servo.angle = 0
#             sleep(2)
#             servo.angle = 90
#             sleep(2)
#             servo.angle = 0
#             sleep(2)
#             servo.angle = -90
#             sleep(2)
#             servo.angle = 0
#             sleep(2)
#             # control_servo(value)
#             # sleep(0.1)
