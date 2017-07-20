/*
  Library Dependencies:
  -ArduinoJson
  -StandardCplusplus (Arduino)
  -LEDMatrix64
  -Queuer (Part of LEDMatrix64)
*/

#include "Display.h"
#include <Wire.h>
#include <ArduinoJson.h>

Display disp;

void setup()
{
  disp.Init();
  disp.LoadMsg(1, F("$$$  Meme Bot  $$$"));
  disp.LoadMsg(2, F("+++ LIVE COUNT +++"));
  disp.LoadMsg(3, F("=================="));
  disp.LoadMsg(4, F("    Version 5.1   "));
  Serial.begin(115200);
  // while(!Serial){} // Required for the Leonardo

  // ProcessJson("{\"dank\":\"420\"}");

  Wire.begin(8);
  Wire.onReceive(ReceiveWire); // register event
}

void loop()
{
  disp.Refresh();
  disp.ScrollMatrix();
  CheckInput();
}

// { = 123
// } = 125

void ReceiveWire() {
  static String jsonString = "";
  bool isJsonStart, isJsonEnd;
  while (0 < Wire.available()) {
    char c = Wire.read();
    if(c == '{') {
      jsonString = "";      
    }
    jsonString = String(jsonString + c);
    if(c == '}') {
      isJsonEnd = true;
      ProcessJson(jsonString);
      break;
    }
  }
}

void ProcessJson(String jsonString) {
  Serial.print(F("Recieved: "));
  Serial.println(jsonString);

  StaticJsonBuffer<200> jsonBuffer1;
  JsonObject& rootR = jsonBuffer1.parseObject(jsonString);
  StaticJsonBuffer<200> jsonMainBuffer;
  JsonObject& rootLookup = jsonMainBuffer.parseObject(F("{\"meme\":\"1\",\"dank\":\"2\",\"hot\":\"3\",\"random\":\"4\",\"xxx\":\"3\",\"welcome\":\"4\",\"find\":\"4\",\"help\":\"4\",\"how\":\"4\",\"why\":\"4\",\"share\":\"4\"}"));

  for(JsonObject::iterator it=rootR.begin(); it!=rootR.end(); ++it) 
  {
    const char* key = it->key;
    String keyStr(key);
    int row = rootLookup[keyStr];
    String countVal = rootR[keyStr];
    disp.LoadMsg(row,keyStr);
    disp.LoadMsg(row,":");
    disp.LoadMsg(row,countVal);
  }
}

void CheckInput() {
  if(Serial.available() <= 0) 
    return;
  char c = Serial.read();
  String letter = String(c);
  disp.LoadMsg(1,letter);
}

