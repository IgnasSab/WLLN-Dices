#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define bitrate 9600

class GSM {
    public:
        GSM();
        void sendMessage(String message);
        void receiveMessage();
        void setup();
    private: 
        SoftwareSerial gsm;
        static const int pin_TX = 7;
        static const int pin_RX = 8;
        String phone_number;
};

#endif