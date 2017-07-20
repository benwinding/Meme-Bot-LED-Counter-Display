#include "Network.h"

Network::Network() {}

void Network::Init(const char* ssid, const char* pwd, String memeCounterHost) {
  this->ssid = ssid;
  this->pwd = pwd;
  this->memeCounterHost = memeCounterHost;

  Serial.begin(115200);
  while (!Serial) {} // Needed for Leornado 
  Serial1.begin(115200);
  WiFi.init(&Serial1);
  WiFi.begin((char*) ssid, pwd);

  if (WiFi.status() != WL_CONNECTED) {
    Serial.print(F("Could not connect to access point, with SSID and password"));
  }
  
  IPAddress ip = WiFi.localIP();
  Serial.print(F("IP Address: "));
  Serial.println(ip);
}

void Network::ConnectToServer() {
  int str_len = memeCounterHost.length() + 1; 
  char char_array[str_len];
  memeCounterHost.toCharArray(char_array, str_len);

  client.connect(char_array, 80);  

  String memeType = "dank";
  String request = "GET ";
  request.concat("/value/");
  request.concat(memeType);
  request.concat("/ HTTP/1.1");
  client.println(request);

  String host = "Host: ";
  host.concat(memeCounterHost);

  client.println(host);
  client.println();
}

void Network::RestartConnection() {
  client.stop();
  ConnectToServer();
}

bool Network::NotConnected() {
  return !client.connected();
}

bool Network::HasResponse() {
  return client.available();
}

bool Network::NotTimedOut() {
  static long _startMillis = millis();
  return millis()-_startMillis < TIMEOUT;
}

bool Network::IsHeaderEnd(std::vector<int> last) {
  // [13][10][13][10] <- end of header characters
  return 
    last[0] == 13 && 
    last[1] == 10 && 
    last[2] == 13 && 
    last[3] == 10;
}

String Network::GetResponse() {
  String readBuffer;
  
  char c;
  std::vector<int> last = {0,0,0,0};
  while((c = client.read()) > 0 ){
    last.erase(last.begin());
    last.push_back(c);
    //if (IsHeaderEnd(last)) {
      readBuffer = client.readString();
      break;
    //}
  }
  Serial.println();
  Serial.print("Response: ");
  Serial.println(readBuffer);
  return readBuffer;
}
