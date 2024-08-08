#include "Dice.h"

Dice::Dice() {
}

void Dice::setup() {
    pinMode(this->pin_vibrating_motor, OUTPUT);
}

void Dice::startThrow() {
    digitalWrite(this->pin_vibrating_motor, HIGH);

}

void Dice::stopThrow() {
    digitalWrite(this->pin_vibrating_motor, LOW);

}