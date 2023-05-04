// EMF Detector Attiny85 and 4 led v1.0
// 23.10.2015
// original code/project by Aaron ALAI - aaronalai1@gmail.com
// modified for use by Giovanni Gentile - giovanni@0lab.it
// Added RS232 Communications by John Sanchez - johns67467@gmail.com
//              Attiny 85
//                ____
//       Reset  -      - vcc+
//          led -      - led
//  1Moh + ante -      - led
//          GND -      - led
//
// Put the 1 Mohm resistor to pin 3 and GND and put antenna

//#include <Manchester.h>
#include <SoftwareSerial.h>
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
//#define tx 0  //pin where your transmitter is connected
#define rx 0
#define tx 2
//uint16_t txdata = 0;

// Set up a new SoftwareSerial object
SoftwareSerial serial(rx, tx); // from Attiny85 to the Pi

int senseLimit = 500; // raise this num to decrease sensitivity
int val = 0; 
int antenna = A2;

// Variables for smoothing
int readings[NUMREADINGS];
int index = 0;
int total = 0;
int averange = 0;

void setup() {
// Set the baud rate for the SoftwareSerial object
    serial.begin(4800);
      
//  pinMode(2, OUTPUT);
//  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);
//  pinMode(A2, INPUT);

// Test leds
//  digitalWrite(2,HIGH);
//  delay(1000);
//  digitalWrite(2,LOW);
//  delay(500);
//  digitalWrite(1,HIGH);
//  delay(1000);
//  digitalWrite(1,LOW);
//  delay(500);
  digitalWrite(3,HIGH);
  delay(1000);
  digitalWrite(3,LOW);
  delay(500);
  
// Initialize all the readings
  for (int i = 0; i < NUMREADINGS; i++) {
  readings[i] = 0;
  }
 //man.setupTransmit(tx, MAN_1200);
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
      serial.println(averange);
      delay(1000);
    }
    
    if (averange > 750) {
      digitalWrite(3,HIGH);  //Optional visual LED for moderate EMF field readings.
      delay(500);
    }
  
    if (averange > 950) {
      //digitalWrite(1,HIGH); //Optional visual LED for high EMF field readings.      
      //delay(500);
    }
    else {
      //digitalWrite(1,LOW);
    }
  }
}
