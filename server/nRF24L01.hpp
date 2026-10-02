#pragma once

#include <iostream>
#include <string>
#include "Color.hpp"

#include "RF24/RF24.h"


class nRF24L01
{
    private :
        const uint64_t _pipe = 0xE8E8F0F0E1LL;

    public :
        nRF24L01(void);
        // nRF24L01(const nRF24L01 &copy);
		// nRF24L01& operator=(const nRF24L01 &copy);
        ~nRF24L01(void);

        // Other function
        void ReceiveCommand(int &angle, int &power);
};
