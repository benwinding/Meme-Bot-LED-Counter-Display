/*
  Library Dependencies:
  -WiFiEsp
  -ArduinoJson
  -StandardCplusplus (Arduino)
  -LEDMatrix64
  -Queuer (Part of LEDMatrix64)
*/

#include "Display.h"
#include "Network.h"

Display disp;
Network network;

//char const* ssid = "Ben's iPhone";
//char const* pwd = "reallylongpassword";
const char* ssid = "The LANnisters 2.4";
const char* pwd = "huskyvalley292";

String memeCounterHost = "butter-goal.glitch.me";

void setup()
{
  disp.Init();
  disp.LoadMsg(1, "Hello World!");

  network.Init(ssid, pwd, memeCounterHost);
  delay(1000);
  String response = GetRespons();
  disp.LoadMsg(2, response);
}

void loop()
{
  disp.Refresh();
  disp.ScrollMatrix();
  //CheckNetwork();
}

void CheckNetwork() {
  static uint32_t lastCountTime = millis();
  if (millis() - lastCountTime > 1500) {
    lastCountTime = millis();
    RunCheckNetwork();
  }  
}

void RunCheckNetwork() {
  if(network.NotConnected()) {
    network.RestartConnection();
  }
  if(network.HasResponse()) {
    String response = network.GetResponse();
    disp.LoadMsg(2, response);
  }
}

String GetRespons() { 
  long _startMillis = millis();
  network.ConnectToServer();
  while (network.NotConnected() and (millis()-_startMillis < 4000))
  {}
  return network.GetResponse();  
}

