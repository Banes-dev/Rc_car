# Rc Car

Project for control different part of my future Rc Car.

I manage firstly my servo motor for turn, after this my motor for forward and after this i want to put a camera and connect my pc or my phone for control the car with different controller like ps4 controller, steering weel, keyboard and simply with a button on the app.

Launch `sudo pigpiod` before

### To Do :
- Mettre condensateur sur module nRF24L01 (x4), tresser deux cables et baisser frequence de communication
- Controller les servo avec autre lib gpio pour un meilleur pwm
- Acheter batterie (~3000mAh, 11.1V = lipo 3S) et acheter chargeur de batterie
- Mettre batterie vers pin de redirection -> regulateur de tension pour raspberry pi 0, direct vers L298N pour alimenter moteur
- Acheter roue (jantes dorées ?)

- Create motor class and manage motor with WiringPi (GPIO)
- Replace servo manage with WiringPi to Pigpio, better PWM precision (needed for servo)
- Communication between client and server with nRF24L01
