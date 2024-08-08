#include "src/Controller.h"


Controller controller;

void collect_garbage();


void setup() {

    Serial.begin(9600);

    controller.setup(); // Must do all pinModes in setup, otherwise it doesn't work

    // Wait for python to send a signal
    while (!Serial.available()) {
        ; // Do nothing
    }
    collect_garbage();
}

void loop() {

    controller.performIteration();

    if (controller.getIterationNum() != 0 && controller.getIterationNum() % controller.getMessageIterations() == 0) {
        controller.sendInfo();
    }
    
}

void collect_garbage() {
    String garbage_collector = Serial.readStringUntil('\n');
}