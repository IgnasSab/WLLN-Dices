#include "src/Controller.h"


Controller controller;

void setup() {
    Serial.begin(9600);

}

void loop() {

    controller.performIteration();

    if (controller.getIterationNum() != 0 && controller.getIterationNum() % controller.getMessageIterations() == 0) {
        controller.sendInfo();
    }

    delay(10); // Repeat it all again
    
}