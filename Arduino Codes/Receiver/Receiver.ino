// Code for RF Receiver
#include <VirtualWire.h>

const int led_pin = 13;
const int receive_pin = 11;
//const int transmit_en_pin = 3;
//const int transmit_pin = 12;

void setup()
{
  // Debug message to check setup status.
  delay(1000);
  Serial.begin(9600);
  Serial.println("Setup is complete.");

  // Initialise the IO and ISR
  //    vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  //    vw_set_ptt_pin(transmit_en_pin);

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
    //      digitalWrite(led_pin, LOW);
  }

  count += 1;

  if (count == timeout) {
    count = 0;
    digitalWrite(led_pin, LOW);
  }

  delay(1000);
}
