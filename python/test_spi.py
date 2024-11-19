import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time

radio = NRF24()
radio.begin(22, 0)  # CE pin, CSN pin
radio.setPALevel(NRF24.PA_HIGH)
radio.setChannel(42)

radio.openWritingPipe(0xE8E8F0F0E1LL)
radio.stopListening()

while True:
    msg = "Test"
    radio.write(msg.encode('utf-8'))
    print("Message envoyé: {}".format(msg))
    time.sleep(1)
