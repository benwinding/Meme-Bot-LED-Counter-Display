JsonObject& ReadClient(WiFiEspClient client)
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
      readBuffer = client.readString();
      break;
    }
  }
  //Serial.println(readBuffer);
  StaticJsonBuffer<500> jsonBuffer;
  return jsonBuffer.parseObject(readBuffer);
}
