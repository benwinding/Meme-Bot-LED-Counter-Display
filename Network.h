#ifndef _NETWORK_H_
#define _NETWORK_H_

// NETWORK definitions
#include "WiFiEsp.h"
#include "Arduino.h"
#include <ArduinoJson.h>
#include <StandardCplusplus.h>
#include <vector>

class Network {
public:
  Network();
  void Init(const char* ssid, const char* pwd, String memeCounterHost);
  String GetMemeCount(String memeType);

private:
  WiFiEspClient client;

  void ConnectToClient(String memeType);
  String ReadClient(WiFiEspClient client);
  const char* ssid;
  const char* pwd;
  String memeCounterHost;
};

#endif
