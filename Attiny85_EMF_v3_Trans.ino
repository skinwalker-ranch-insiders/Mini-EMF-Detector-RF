// EMF Detector Attiny85 and 4 led v1.0
// 23.10.2015
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use by Giovanni Gentile - giovanni@0lab.it
// Added RF315 Communications via Pin 0 by John Sanchez - johns67467@gmail.com
//              Attiny 85
//                ____
//       Reset  -      - vcc+
//          led -      - led
//  1Moh + ante -      - led
//          GND -      - led
//
// Put the 1 Mohm resistor to pin 3 and GND and put antenna

#include <Manchester.h>
#define NUMREADINGS 15 // Number of readings

/*
  Manchester Transmitter example
  In this example transmitter will send one 16 bit number
  per transmission.
  Try different speeds using these constants, your maximum
  possible speed will depend on various factors like transmitter
  type, distance, microcontroller speed, ...
  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7
*/
#define TX_PIN 0  //pin where your transmitter is connected

int senseLimit = 500; // raise this num to decrease sensitivity
int val = 0; 
int antenna = A2;

int LED[] = {2,1,3};

// Variables for smoothing
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int averange = 0;
uint16_t transmit_data;

void setup() {
  
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(A2, INPUT);

// Test leds
  digitalWrite(LED[2],HIGH);
  delay(1000);
  digitalWrite(LED[2],LOW);
  delay(500);
  digitalWrite(LED[1],HIGH);
  delay(1000);
  digitalWrite(LED[1],LOW);
  delay(500);
  digitalWrite(LED[3],HIGH);
  delay(1000);
  digitalWrite(LED[3],LOW);
  delay(500);
  
// Initialize all the readings
  for (int i = 0; i < NUMREADINGS; i++) {
  readings[i] = 0;
  }
 man.setupTransmit(TX_PIN, MAN_1200);
}

void loop() {
  int val = analogRead(antenna);
  
  if(val >= 1){
    
    val = constrain(val, 1, senseLimit); // turn any readings higher than the senseLimit into the senseLmit value
    val = map(val, 1, senseLimit, 1, 1023); // remap the values
    
    total -= readings[index]; // subtract the last reading
    readings[index] = val;    // read from the sensor
    total+= readings[index];  // add the reading to the total
    index = (index + 1);      // advance to the next index
    
    if (index >= NUMREADINGS)
      index = 0;
  
    averange = total / NUMREADINGS;
    
    if (averange > 350) {
      digitalWrite(2,HIGH);
    }
    else {
      digitalWrite(2,LOW);
    }

    if (averange > 750) {
      digitalWrite(1,HIGH);
      man.transmit(averange);
      delay(200);
    }
    else {
      digitalWrite(1,LOW);
    }
  
    if (averange > 950) {
      digitalWrite(3,HIGH);
      man.transmit(averange);
      delay(200);
    }
    else {
      digitalWrite(3,LOW);
    }
  }
}
