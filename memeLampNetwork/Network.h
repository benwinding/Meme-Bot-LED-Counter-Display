#ifndef _NETWORK_H_
#define _NETWORK_H_

// NETWORK definitions
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <vector>

class Network {
public:
  Network();
  void Init(const char* ssid, const char* pwd, String memeCounterHost);
  void ConnectToServer();
  void RestartConnection();
  bool NotConnected();
  bool HasResponse();
  String GetResponse();
  bool GetResponsePartial();

  WiFiClient client;
  String readBuffer;

private:
  const char* ssid;
  const char* pwd;
  String memeCounterHost;

  int TIMEOUT;
  bool IsHeaderEnd(std::vector<int> last);
  bool NotTimedOut();
};

#endif
