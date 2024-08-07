#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Dice.h"
#include "RPI_COM.h"
#include "Components.h"

#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "Arduino.h"
#define int uint32_t

#define throw_delay 1000 // Hardcoded value


class Controller {
    public:
        Controller();
        void performIteration();
        int getIterationNum();
        void sendInfo();
        int getMessageIterations();

        void throwDice();
    private:
        void getData();
        void processData();
        void displayProcessedData();
        // LiquidCrystal_I2C lcd;
        GSM gsm;
        Dice dice;
        RPI_COM rpi_com;
        int dice_sum;
        int iteration_num;
        int current_pip_num;
        double average;
        static const int message_iterations = 5;
};

#endif