/*
  Library Dependencies:
  -WiFiEsp
  -ArduinoJson
  -StandardCplusplus (Arduino)
  -LEDMatrix64
  -Queuer (Part of LEDMatrix64)
*/

#include "Display.h"
#include <Wire.h>

Display disp;

  const int sclPin = 3;
  const int sdaPin = 2;

void setup()
{
  disp.Init();
  disp.LoadMsg(1, "Hello World!");
  Serial.begin(115200);
  while(!Serial){}

//  Wire.begin(sdaPin, sclPin);

  Wire.begin(8);
  Wire.onReceive(ReceiveWire); // register event
}

void loop()
{
  disp.Refresh();
  disp.ScrollMatrix();
  CheckInput();
}

void ReceiveWire() {
  while (0 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
    String letter = String(c);
    disp.LoadMsg(3,letter);
  }
}

void CheckInput() {
  if(Serial.available() <= 0) 
    return;
  char c = Serial.read();
  String letter = String(c);
  disp.LoadMsg(4,letter);
}

