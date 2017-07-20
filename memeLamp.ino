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
  network.ConnectToServer();
}

void loop()
{
  disp.Refresh();
  disp.ScrollMatrix();
  CheckNetwork();
}

void CheckNetwork() {
  if(!network.HasResponse()) 
    return;
  if(network.GetResponsePartial()) {
    String response = network.readBuffer;
    disp.LoadMsg(2, response);
  }
}

void CheckNetwork1() {
  if(!network.HasResponse()) 
    return;
  if(network.NotConnected()) {
    network.RestartConnection();
  }
  String response = network.GetResponse();
  disp.LoadMsg(2, response);
}


