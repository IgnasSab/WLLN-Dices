#include "Components.h"

GSM::GSM() : gsm(this->pin_TX, this->pin_RX) {
    this->gsm.begin(bitrate);
    this->phone_number = "+37062169269"; // Hard code it
}

void GSM::sendMessage(String message) {
  this->gsm.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  this->gsm.println("AT+CMGS=\"" + String(this->phone_number) + "\"\r"); //Mobile phone number to send message
  delay(1000);
  this->gsm.println(message); // Messsage content
  delay(100);
  this->gsm.println((char) 26);// ASCII code of CTRL+Z
  delay(1000);
}

void GSM::receiveMessage() {

}