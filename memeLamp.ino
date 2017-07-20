#include <ArduinoJson.h>
#include "WiFiEsp.h"
#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>

// Emulate Serial1 on pins 7/6 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial1(6, 7); // RX, TX
#endif

const char* ssid = "The LANnisters 2.4";
const char* pwd= "huskyvalley292";
//char ssid[] = "Ben's iPhone";
//char pwd[] = "reallylongpassword";

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
  while(!Serial){}
  WiFi.init(&Serial1);

  WiFi.begin(ssid, pwd);
  if(WiFi.status() != WL_CONNECTED)
  {
  	Serial.print("Could not connect to access point, with SSID and password");
  }
  
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop()
{
  WiFiEspClient client;
  
  const char* host = "butter-goal.glitch.me";
  const char* request = "GET / HTTP/1.1";
  const char* header = "Host: butter-goal.glitch.me";
  WiFi.ping(host);
  client.connect(host, 80);
  client.println(request);
  client.println(header);
  client.println();

  ReadClient(client);

  client.stop();

  delay(10000);
}

void ReadClient(WiFiEspClient client)
{
  long _startMillis = millis();
  while (!client.available() and (millis()-_startMillis < 2000))
  {}

  String readBuffer;
  
  char c;
  std::vector<int> last = {0,0,0,0};
  while((c = client.read()) > 0 ){
    last.erase(last.begin());        
    last.push_back(c);
    
    if (last[0] == 13 && last[1] == 10 && last[2] == 13 && last[3] == 10) {
      // [13][10][13][10] <- end of header characters
      Serial.println(c);
      readBuffer = client.readString();
      break;
    }
  }

  Serial.println(readBuffer);
  Serial.println();

  StaticJsonBuffer<500> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(readBuffer);
  const char* dank = root["dank"];
  Serial.print("Dank is:");   
  Serial.println(dank);
}

