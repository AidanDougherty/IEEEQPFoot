#include <SoftwareSerial.h>


// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <stdio.h>
#include <stdlib.h>

// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
SoftwareSerial EEBlue(19,18); // RX | TX

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  delay(500);
  EEBlue.begin(9600);
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
//  Serial.print("X:  "); Serial.print(lis.x); 
//  Serial.print("  \tY:  "); Serial.print(lis.y); 
//  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  /*Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
  Serial.println(" m/s^2 ");

  Serial.println();
  */
  
  //EEBlue.write(event.acceleration.z);
  char a[10];
  char a2[10];
  double accel = event.acceleration.z;
  sprintf(a, "%d", (int)accel); 
  sprintf(a2, "%d", (int)((accel-(int)accel)*1000));

  //Print accel
  
  EEBlue.write(a);
  EEBlue.write(".");
  EEBlue.write(a2);
  EEBlue.write(" ");
  

  //Print Pressure Sensors
  
  char sp[10];
  for(int i = 0; i<3; i++){
    int pressure = analogRead(i);
    sprintf(sp,"%d",pressure);
    EEBlue.write(sp);
    EEBlue.write(" ");
  }
  EEBlue.write("\n");
  //Serial.print(s);
  
  
 
  delay(200); 
}
