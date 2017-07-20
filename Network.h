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
  void ConnectToServer();
  void RestartConnection();
  bool NotConnected();
  bool HasResponse();
  String GetResponse();

  WiFiEspClient client;

private:
  const char* ssid;
  const char* pwd;
  String memeCounterHost;

  int TIMEOUT;
  bool IsHeaderEnd(std::vector<int> last);
  bool NotTimedOut();
};

#endif
