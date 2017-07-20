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

void Network::ConnectToClient(String memeType) {
  int str_len = memeCounterHost.length() + 1; 
  char char_array[str_len];
  memeCounterHost.toCharArray(char_array, str_len);

  client.connect(char_array, 80);  

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

String Network::GetMemeCount(String memeType) {
  ConnectToClient(memeType);
 
  String str = ReadClient(client);
  client.stop();

  return str;
}

String Network::ReadClient(WiFiEspClient client)
{
  long _startMillis = millis();
  while (!client.available() and (millis()-_startMillis < 4000))
  {}

  String readBuffer;
  
  char c;
  std::vector<int> last = {0,0,0,0};
  while((c = client.read()) > 0 ){
    last.erase(last.begin());
    last.push_back(c);
    if (last[0] == 13 && last[1] == 10 && last[2] == 13 && last[3] == 10) {
      // [13][10][13][10] <- end of header characters
      readBuffer = client.readString();
      break;
    }
  }
  Serial.println(readBuffer);
  return readBuffer;
}

