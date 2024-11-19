#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "nRF24L01.hpp"

int main(int argc, char **argv)
{
    void(argc);
    void(argv);
    nRF24L01 module;

    std::cout << Blue << " Client started " << Green << "✔" << std::endl;
    while(true)
    {
        // std::string command;
        // std::getline(std::cin, command);
        module.SendCommand(42, 42);
        // delay(6);
        // Sleep(6);
        std::this_thread::sleep_for(std::chrono::milliseconds(6)); // 6ms de delai
    }
    return (0);
}
