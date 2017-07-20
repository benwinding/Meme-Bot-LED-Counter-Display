#include <StandardCplusplus.h>
#include <serstream>
#include <string>
#include <vector>
#include <iterator>
#include <ArduinoJson.h>

#include "WiFiEsp.h"

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
  {
  }

  char c;
  bool beginPrint = false;
  int byteCount = 300;
  std::vector<int> last = {1,2,3,4,5};
  while((c = client.read()) > 0 and (byteCount > 0)){
    if (c == '{' )
      beginPrint = true;      
    if(beginPrint)
      Serial.print(c);
    else{
      if(last.size() > 30) {
        last.erase(last.begin());        
      } 
      last.push_back((int) c);        
    }
    byteCount--;
  }

  Serial.println();
  Serial.print("Vector is size: "); Serial.println((int) last.size());
  Serial.println("Last characters printed: ");
  for (int i=0; i< last.size(); i++)
  {
    Serial.print("[");
    Serial.print((int) last.at(i));
    Serial.print("]");
  }
  Serial.println();
}

