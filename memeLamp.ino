/*
  Library Dependencies:
  -WiFiEsp
  -ArduinoJson
  -StandardCplusplus (Arduino)
  -LEDMatrix64
  -Queuer (Part of LEDMatrix64)
*/

#include "Network.h"
#include <Wire.h>

Network network;

//char const* ssid = "Ben's iPhone";
//char const* pwd = "reallylongpassword";
const char* ssid = "The LANnisters 2.4";
const char* pwd = "huskyvalley292";

String memeCounterHost = "butter-goal.glitch.me";

void setup()
{
  network.Init(ssid, pwd, memeCounterHost);
  network.ConnectToServer();
  Serial.begin(115200);
  Serial.println();
  
  const int sclPin = D1;
  const int sdaPin = D2;
  
  Wire.begin(sdaPin, sclPin);
  
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("lastResponse");        // sends five bytes
  Wire.endTransmission();    // stop transmitting
}

void loop()
{
  CheckNetwork();
}

void CheckNetwork() {
  if(network.NotConnected()) {
    network.RestartConnection();
  }
  if(!network.HasResponse()) 
    return;
  String response = network.GetResponse();
  static String lastResponse = "";
  if(response.equals(lastResponse))
    return;
  lastResponse = String("" + response);
  Serial.println(response);

  int str_len = lastResponse.length() + 1; 
  char char_array[str_len];
  lastResponse.toCharArray(char_array, str_len);
  Serial.println(char_array);

  Wire.beginTransmission(8); // transmit to device #8
  Wire.write(char_array);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
}

