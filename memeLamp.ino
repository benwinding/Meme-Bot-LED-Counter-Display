#include "WiFiEsp.h"
#include "LEDMatrix.h"
#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <vector>

#include "LedMatrixFont.h"

//// Emulate Serial1 on pins 7/6 if not present
//#ifndef HAVE_HWSERIAL1
//#include "SoftwareSerial.h"
//SoftwareSerial Serial1(6, 7); // RX, TX
//#endif

//const char* ssid = "The LANnisters 2.4";
//const char* pwd = "huskyvalley292";
const char ssid[] = "Ben's iPhone";
const char pwd[] = "reallylongpassword";

#include "LEDMatrix.h"
#include "LedMatrixFont.h"

#define WIDTH   64
#define HEIGHT  16

const byte oe = A0;
const byte r1 = A1;

const byte a = 11;
const byte b = 10;
const byte c = 9;
const byte d = 8;

const byte stb = A2; //le
const byte clk = A3;

LEDMatrix matrix(a, b, c, d, oe, r1, stb, clk);

// Display Buffer 128 = 64 * 16 / 8
uint8_t displaybuf[WIDTH * HEIGHT / 8] = {};

void setup()
{
  matrix.begin(displaybuf, WIDTH, HEIGHT);

  Serial.begin(115200);
  Serial1.begin(115200);
  // while (!Serial) {}
  WiFi.init(&Serial1);

  WiFi.begin(ssid, pwd);
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(F("Could not connect to access point, with SSID and password"));
  }

  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);
  //WiFi.ping("butter-goal.glitch.me");
}

char* lastDank = "         ";

void loop()
{
  WiFiEspClient client;
  client.connect("butter-goal.glitch.me", 80);
  client.println(F("GET / HTTP/1.1"));
  client.println(F("Host: butter-goal.glitch.me"));
  client.println();

  JsonObject& root = ReadClient(client);

  const char* dank = root["dank"];

  client.stop();

  Serial.print("last: ");Serial.print(lastDank);
  Serial.print(", curr: ");Serial.print(dank);
  Serial.println();

  if(strcmp(dank, lastDank) == 0) {
    return;    
  }

  // Copy new value into old string
  snprintf(lastDank, strlen(dank)+1, "%s", dank);
  
  //Draw on led screen
  uint32_t lastCountTime = millis();
  while ((millis() - lastCountTime) < 2000) {
    DrawSentence(dank);
    ShowMatrix(30);
  }
  delay(50);
}


