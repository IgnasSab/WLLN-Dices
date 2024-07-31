#ifndef DICE_H
#define DICE_H

#include <Arduino.h>

class Dice {
    public:
        Dice();
        void startThrow();
        void stopThrow();
    private:
        const static int pin_vibrating_motor = 6;

};


#endif