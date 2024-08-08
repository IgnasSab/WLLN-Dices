#include "RPI_COM.h"

RPI_COM::RPI_COM() {

}

void RPI_COM::setup() {
    // NO setup required
}

void RPI_COM::sendPacket() {
    Serial.println("CAPTURE");    
}

int RPI_COM::receivePacket() {
    int pip_number;
    while (!Serial.available()) {
        ; // Do nothing
    }
    pip_number = Serial.readStringUntil('\n').toInt();
    return pip_number;
}

