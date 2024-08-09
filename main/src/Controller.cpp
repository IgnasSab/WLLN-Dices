#include "Controller.h"

Controller::Controller() {
    this->dice_sum = 0;
    this->iteration_num = 0;
    this->average = -1;
    this->current_pip_num = -1;
    this->running = false;
}

String parsePhoneNumber(String data) {
    // Find the position of the first quote
    int startIndex = data.indexOf('\"') + 1; // Move to the character after the first quote
    int endIndex = data.indexOf('\"', startIndex); // Find the next quote

    // Extract the phone number using substring
    return data.substring(startIndex, endIndex);
}

String parseMessageContent(String data) {
    // Find the position of the newline character
    int newlineIndex = data.indexOf('\n', 2);

    // Extract the message content after the newline
    if (newlineIndex != -1) {
        return data.substring(newlineIndex + 1, data.length() - 2); // Get everything after the newline
    }
}
void Controller::startStop() {
    if (this->gsm.receivedMessage()) {
        String msg = this->gsm.readMessage();
        String phone_number = parsePhoneNumber(msg);
        String content = parseMessageContent(msg);
        if (content.equals("start") && phone_number.equals(this->gsm.getNumber()) && this->running == false) {
            this->running = true;
        } else if (content.equals("stop") && phone_number.equals(this->gsm.getNumber()) && this->running == true) {
            this->running = false;
        }
    }
}

void Controller::setup() {
    this->dice.setup();
    this->rpi_com.setup();
    this->gsm.setup();
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

bool Controller::isRunning() {
    return this->running;
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
    delay(throw_delay);
}
void Controller::getData() {
    this->rpi_com.sendPacket();
    delay(100);
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