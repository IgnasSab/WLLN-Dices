#include "Controller.h"
//  lcd(0x27, 20, 4)

Controller::

Controller::Controller() {
    this->dice_sum = 0;
    this->iteration_num = 0;
    this->average = -1;
    this->current_pip_num = -1;
}

int Controller::getMessageIterations() {
    return this->message_iterations;
}

int Controller::getIterationNum() {
    return this->iteration_num;
}

void Controller::sendInfo() {
    this->gsm.sendMessage("Running average: " + String(this->average)
                                    + "Iteration: " 
                                    + String(this->iteration_num));
}

void Controller::performIteration() {
    this->throwDice();
    this->getData();
    this->displayProcessedData();
}

void Controller::throwDice() {
    this->dice.startThrow();
    delay(throw_delay);
    this->dice.stopThrow();
}
void Controller::getData() {
    this->rpi_com.sendPacket();
    delay(10);
    this->current_pip_num = this->rpi_com.receivePacket();
    this->processData();
}
void Controller::processData() {
    if (this->current_pip_num != -1) {
        this->iteration_num++;
        this->dice_sum += this->current_pip_num;
        this->average = (double) this->dice_sum  / (double) this->iteration_num;
    }
}
void Controller::displayProcessedData() {
    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Running average: ");
    // lcd.setCursor(0, 18);
    // lcd.print(this->average); // TODO could cause problems
    // lcd.setCursor(1, 0);
    // lcd.print("Iteration: ");
    // lcd.setCursor(1, 13);
    // lcd.print(this->iteration_num);
    // lcd.setCursor(2, 0);
    // lcd.print("Current dice: ");
    // lcd.setCursor(15);
    // lcd.print(this->current_pip_num);

    // Serial.print("Running average: ");
    // Serial.print(this->average); // TODO could cause problems
    // Serial.print("Iteration: ");
    // Serial.print(this->iteration_num);
    // Serial.print("Current dice: ");
    // Serial.println(this->current_pip_num);
}