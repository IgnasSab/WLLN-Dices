#include "src/Controller.h"


void setup() {
    Serial.begin(9600);

    Serial.println("START");
}

void loop() {


    controller.throwDice();

    controller.getData();

    controller.displayData();
    
}