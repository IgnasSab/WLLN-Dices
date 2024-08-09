#include "Components.h"

GSM::GSM() : gsm(this->pin_TX, this->pin_RX) {
}

String GSM::readMessage() {
  String message = "";
  while (this->gsm.available()) {
    char c = this->gsm.read();
    message += c;
  }
  return message;
}

String GSM::getNumber() {
  return this->phone_number;
}

bool GSM::receivedMessage() {
  return this->gsm.available();
}


void GSM::setup() {
    this->gsm.begin(bitrate);
    this->phone_number = "+37062169269"; // Hard code it
    this->gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
}

void GSM::sendMessage(String message) {
  this->gsm.println("AT+CMGS=\"" + String(this->phone_number) + "\"\r"); //Mobile phone number to send message
  delay(1000);
  this->gsm.println(message); // Messsage content
  delay(100);
  this->gsm.println((char) 26);// ASCII code of CTRL+Z
  delay(1000);
}