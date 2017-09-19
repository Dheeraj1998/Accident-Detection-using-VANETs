// Code for RF transmitter
#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 9;
int accident_bool = 7;
//const int receive_pin = 2;
//const int transmit_en_pin = 3;

void setup() {

  // Initialise the Transmit pins
  vw_set_tx_pin(transmit_pin);
  //    vw_set_rx_pin(receive_pin);
  //    vw_set_ptt_pin(transmit_en_pin);

  // Required for DR3100
  vw_set_ptt_inverted(true);

  // Bits per sec
  vw_setup(2000);

  // Setting up the pins
  pinMode(led_pin, OUTPUT);
  pinMode(accident_bool, INPUT);

  //    Setting up the Serial Monitor
  //    Serial.begin(9600);
}

// Setting up the length of the message
const int message_length = 20;

// Setting up the unique UUID of the vehicle
char msg[message_length] = {'d', '1', 'f' , '6', 'e', '2', '3', 'f', '-', '4', 'a', 'e', '2', '-', '4', '3', '5', '2', '-', '3'};

void loop() {

  // Triggering the RF transmitter on accident.
  //if(digitalRead(accident_bool) == 1) {
  if (1) {

    // On accident, infinite loop is activated.
    while (true) {
      // Flash a light to show transmitting
      digitalWrite(led_pin, HIGH);
      vw_send((uint8_t *)msg, message_length);

      // Wait until the whole message is transmitted.
      vw_wait_tx();
      digitalWrite(led_pin, LOW);
      delay(1000);
    }
  }
}
