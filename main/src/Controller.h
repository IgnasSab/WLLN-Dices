#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Dice.h"
#include "RPI_COM.h"
#include <LiquidCrystal_I2C.h>
#include "Arduino.h"
#define int uint32_t

#define throw_delay 2000; // Hardcoded value


class Controller {
    public:
        Controller();
        void throwDice();
        void getData();
        void processData();
        void displayInfo();

    private:
        LiquidCrystal_I2C lcd;
        Dice dice;
        RPI_COM rpi_com;
        int dice_sum;
        int iteration_num;
        int current_pip_num;
        double average;
};

#endif