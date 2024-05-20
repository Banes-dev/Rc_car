from gpiozero import AngularServo
from time import sleep

# Utils function
def map_value(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

servo = AngularServo(18, min_pulse_width=0.0006, max_pulse_width=0.0023)

while (True):
    # function for get joystick nb
    # if nb_joystick > 0
        # transfor joystick nb with map function between -20 and 90
    # if nb_joystick > 0
        # transfor joystick nb with map function between -90 and 0
    servo.angle = -20
    sleep(0.2)
    servo.angle = 90
    sleep(0.2)
    servo.angle = -20
    sleep(0.2)
    servo.angle = -90
    sleep(0.2)

# Export function
def reset_servo():
    servo.angle = -20