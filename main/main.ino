#include "src/Controller.h"

#define regular_delay 1000

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
    
    delay(regular_delay);
}

void loop() {

    controller.startStop(); // Waits for an sms for starting and stopping the robot

    if (controller.isRunning()) {
        controller.performIteration(); // Performs a single iteration 
    } else {
        delay(regular_delay); // Make a delay if the robot is stopped
    }

    if (controller.getIterationNum() != 0 && controller.getIterationNum() % controller.getMessageIterations() == 0) {
        controller.sendInfo(); // Send an sms message if the specific amount of iterations have passed
    }
    
}

void collect_garbage() {
    String garbage_collector = Serial.readStringUntil('\n');
}