/*
  Library Dependencies:
  -ArduinoJson
  -WiFiEsp
  -StandardCplusplus (Arduino)
  -Queuer (Part of LEDMatrix64)
*/

#include "Network.h"
#include <Wire.h>
#include <ArduinoJson.h>

Network network;

//char const* ssid = "Ben's iPhone";
//char const* pwd = "reallylongpassword";
const char* ssid = "The LANnisters 2.4";
const char* pwd = "huskyvalley292";

String memeCounterHost = "butter-goal.glitch.me";

void setup() {
  network.Init(ssid, pwd, memeCounterHost);
  network.ConnectToServer();
  Serial.begin(115200);
  Serial.println();
  
  const int sclPin = D1;
  const int sdaPin = D2;
  
  Wire.begin(sdaPin, sclPin);
}

void loop() {
  CheckNetwork();
}

void CheckNetwork() {
  if(network.NotConnected()) {
    network.RestartConnection();
  }
  if(!network.HasResponse()) 
    return;
  String response = network.GetResponse();
  static String lastResponse = "{\"Request\":\"Count\",\"meme\":\"2405\",\"dank\":\"2147\",\"hot\":\"1161\",\"random\":\"331\",\"xxx\":\"1304\",\"welcome\":\"127\",\"find\":\"53\",\"help\":\"42\",\"how\":\"2\",\"why\":\"12\",\"share\":\"3\"}";
  if(response.equals(lastResponse))
    return;
  String changedJson = GetChange(lastResponse, response);

  lastResponse = String("" + response);

  Serial.println(changedJson);
  SendWire(changedJson);
}

String GetChange(String previous, String current) {
  StaticJsonBuffer<400> jsonBufferP;
  StaticJsonBuffer<400> jsonBufferC;
  JsonObject& rootP = jsonBufferP.parseObject(previous);
  JsonObject& rootC = jsonBufferC.parseObject(current);

//  Serial.print("Prev: ");
//  Serial.println(previous);
//  Serial.print("Curr: ");
//  Serial.println(current);

  for(JsonObject::iterator it=rootP.begin(); it!=rootP.end(); ++it) 
  {
    const char* key = it->key;
    String keyStr(key);
    String valueP = rootP[keyStr];
    String valueC = rootC[keyStr];
    if(!valueP.equals(valueC)) {
      StaticJsonBuffer<100> jsonBuffer2;
      JsonObject& root2 = jsonBuffer2.createObject();
      root2[key] = valueC;
      String buf = "";
      root2.printTo(buf);
      return buf;
    }
  }
  return "NOT FOUND";
}

void SendWire(String response) {
  int str_len = response.length() + 1; 
  char char_array[str_len];
  response.toCharArray(char_array, str_len);

  for(int i=0; i<str_len; i++) {
    Wire.beginTransmission(8); // transmit to device #8
    Wire.write(char_array[i]);
    Wire.endTransmission();    // stop transmitting
  }
}


