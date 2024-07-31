#include "src/Controller.h"


void setup() {
    Serial.begin(9600);

    Serial.println("START");
}

void loop() {


    dice.throwDice();

    rpi_com.sendPacket(); // Send notification to python 
    rpi_com.receivePacket(); // Wait for information from python
    
}