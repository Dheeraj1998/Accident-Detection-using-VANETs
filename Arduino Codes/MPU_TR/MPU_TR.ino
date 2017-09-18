// Code for setting up the MPU, RF Transmitter and RF Receiver 

// Including the required libraries
#include "I2Cdev.h"
#include "MPU6050.h"
#include <VirtualWire.h>

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
#define OUTPUT_READABLE_ACCELGYRO

// Setting up the gyroscope
MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

// Setting up the Transmitter and Receiver
const int led_pin = 13;
const int transmit_pin = 9;
const int receive_pin = 11;
bool accident_bool = false;

// Timeout before resetting the receiver.
int timeout = 15;
int count = 0;

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize device
    accelgyro.initialize();

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

void loop() {
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if(abs(ay) > 5000){
    accident_bool = true;
  }

  // Extracting the received message.
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;

  // Execute code on receiving message.
  if (vw_get_message(buf, &buflen) or accident_bool) {
    
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
    while(1) {
      // Initialise the Transmit pins
      vw_set_tx_pin(transmit_pin);

      // Required for DR3100
      vw_set_ptt_inverted(true);

      // Bits per sec
      vw_setup(2000);      

      // Setting up the length of the message
      const int message_length = 20;

      // Setting up the unique UUID of the vehicle
      char msg[message_length] = {'d', '1', 'f' ,'6', 'e', '2', '3', 'f', '-', '4', 'a', 'e', '2', '-', '4', '3', '5', '2', '-', '3'};

      if(1) {
    
        // On accident, infinite loop is activated.
        while(true) {
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
