import controller
import servo
from multiprocessing import Process
from time import sleep

def run_controller(queue):
    joystick = controller.check_manette()
    if joystick:
        while True:
            value = controller.get_left_joystick_value(joystick)
            queue.put(value)
            sleep(0.1)

def run_servo(queue):
    while True:
        if not queue.empty():
            value = queue.get()
            servo.control_servo(value)

if __name__ == "__main__":
    from multiprocessing import Queue

    queue = Queue()
    controller_process = Process(target=run_controller, args=(queue,))
    servo_process = Process(target=run_servo, args=(queue,))

    controller_process.start()
    servo_process.start()

    try:
        controller_process.join()
        servo_process.join()
    except KeyboardInterrupt:
        servo.reset_servo()
        print("Programme interrompu par l'utilisateur.")
    finally:
        controller_process.terminate()
        servo_process.terminate()
        print("Program as quit.")
