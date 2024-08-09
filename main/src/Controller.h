#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "Dice.h"
#include "RPI_COM.h"
#include "Components.h"

#define int uint32_t

#define throw_delay 1000 // Hardcoded value


class Controller {
    public:
        Controller();
        void performIteration();
        int getIterationNum();
        void sendInfo();
        int getMessageIterations();
        void setup();
        bool isRunning();
        void startStop();
    private:
        bool running;
        void throwDice();
        void getData();
        void processData();
        void displayProcessedData();
        GSM gsm;
        Dice dice;
        RPI_COM rpi_com;
        int dice_sum;
        int iteration_num;
        int current_pip_num;
        double average;
        static const int message_iterations = 20;
};

#endif