#pragma once

#include <iostream>
#include <string>

#include "RF24/RF24.h"

class nRF24L01
{
    private:
        const uint64_t _pipe = 0xE8E8F0F0E1LL;
    public:
        nRF24L01(void);
        nRF24L01(const nRF24L01 &copy);
		nRF24L01& operator=(const nRF24L01 &copy);
        ~nRF24L01(void);

        // Other function
        int ReceiveCommand(void);
};

// Color
# define Reset_Color "\033[0m"     // Text Reset

# define Black "\033[0;30m"        // Black
# define Red "\033[0;31m"          // Red
# define Green "\033[0;32m"        // Green
# define Yellow "\033[0;33m"       // Yellow
# define Blue "\033[0;34m"         // Blue
# define Purple "\033[0;35m"       // Purple
# define Cyan "\033[0;36m"         // Cyan
# define White "\033[0;37m"        // White

// Arrow
# define Arrow_up "↑"
# define Arrow_down "↓"
# define Arrow_right "→"
# define Arrow_left "←"
