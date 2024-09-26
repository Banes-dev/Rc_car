#include "iostream"
#include "chrono"
#include "thread"

#include "Servo.hpp"

int main(void)
{
    Servo servo;

    std::cout << "Rc Car started ✔" << std::endl;
    while(1)
    {
        std::cout << "← Gauche" << std::endl;
        servo.MoveServo(200);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "↓ Milieux ↓" << std::endl;
        servo.MoveServo(125);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "→ Droite" << std::endl;
        servo.MoveServo(50);
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    return (0);
}
