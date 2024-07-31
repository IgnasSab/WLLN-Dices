#include "Controller.h"

Controller::Controller() : lcd(0x27, 20, 4) {
    dice_sum = 0;
    iteration_num = 0;
    average = 0;
    current_pip_num = 0;

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
    this->dice_sum += this->current_pip_num;
    this->iteration_num += 1;
    this->average = this->dice_sum / this->iterations_num;
}
void Controller::displayInfo() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Running average: ");
    lcd.setCursor(0, 18);
    lcd.print(this->average); // TODO could cause problems
    lcd.setCursor(1, 0);
    lcd.print("Iteration: ");
    lcd.setCursor(1, 13);
    lcd.print(this->iteration_num);
    lcd.setCursor(2, 0);
    lcd.print("Current dice: ");
    lcd.setCursor(15);
    lcd.print(this->current_pip_num);


}