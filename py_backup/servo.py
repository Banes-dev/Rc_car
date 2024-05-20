from gpiozero import AngularServo
from time import sleep
from controller import get_left_joystick

# Utils function
def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

servo = AngularServo(18, min_pulse_width=0.0003, max_pulse_width=0.0023) # min_pulse_width=0.0006, max_pulse_width=0.0023

while (True):
    # function for get joystick nb
    nb_joystick = get_left_joystick()
    print(f"test : {nb_joystick}")
    # if nb_joystick > 0:
        # transfor joystick nb with map function between 0 and 90
    # if nb_joystick < 0:
        # transfor joystick nb with map function between -90 and 0
    # servo.angle = 0
    # sleep(2)
    # servo.angle = 90
    # sleep(2)
    # servo.angle = 0
    # sleep(2)
    # servo.angle = -90
    # sleep(2)

# Export function
def reset_servo():
    servo.angle = -20