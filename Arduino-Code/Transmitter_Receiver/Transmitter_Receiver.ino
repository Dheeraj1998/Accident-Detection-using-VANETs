// Code for setting up both the RF Transmitter and Receiver on the same device

#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 9;
const int receive_pin = 11;
int accident_bool = 7;

void setup() {
  // Debug message to check setup status.
  delay(1000);
  Serial.begin(9600);
  Serial.println("Setup is complete.");

  // Initialise the IO and ISR
  vw_set_rx_pin(receive_pin);

  // Required for DR3100
  vw_set_ptt_inverted(true);

  // Bits per sec
  vw_setup(2000);

  // Start the receiver PLL running
  vw_rx_start();

  // Setting up the pins
  pinMode(led_pin, OUTPUT);
}

// Timeout before resetting the receiver.
int timeout = 15;
int count = 0;

void loop() {
  // Extracting the received message.
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;

  // Execute code on receiving message.
  if (vw_get_message(buf, &buflen)) {

    // Flash a light to show received good message
    digitalWrite(led_pin, HIGH);

    // Message with a good checksum received, dump it.
    Serial.print("Got: ");
    for (int i = 0; i < buflen; i++) {
      Serial.write(buf[i]);
    }
    Serial.println();
    digitalWrite(led_pin, LOW);

    // Stop receiving the messages and start transmitting
    while (1) {
      // Initialise the Transmit pins
      vw_set_tx_pin(transmit_pin);

      // Required for DR3100
      vw_set_ptt_inverted(true);

      // Bits per sec
      vw_setup(2000);

      // Setting up the length of the message
      const int message_length = 20;

      // Setting up the unique UUID of the vehicle
      char msg[message_length] = {'d', '1', 'f' , '6', 'e', '2', '3', 'f', '-', '4', 'a', 'e', '2', '-', '4', '3', '5', '2', '-', '3'};

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

    count += 1;

    if (count == timeout) {
      count = 0;
      digitalWrite(led_pin, LOW);
    }

    delay(1000);
  }
}
