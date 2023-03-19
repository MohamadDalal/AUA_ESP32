
void ScanningWifi(){
  u8g2.clearBuffer();
  u8g2.drawStr(16, 26, "Scanning for");
  u8g2.drawStr(16, 42, "WiFi networks!");
  u8g2.sendBuffer();
}

void PrintedWifi(int NumNetworks){
  u8g2.clearBuffer();
  int StrW1 = u8g2.drawStr(8,16, "Found ");
  u8g2.setCursor(8+StrW1,16);
  u8g2.print(NumNetworks);
  //u8g2.print("Found %i networks!", NumNetworks);
  int StrW2 = log10(NumNetworks)*12;
  u8g2.drawStr(8+StrW1+StrW2,16, " networks!");
  u8g2.drawStr(8, 32, "Printed the results.");
  u8g2.drawStr(8, 48, "to Serial print.");
  u8g2.sendBuffer();
}

void ConnectingWifi(String NetworkName){
  u8g2.clearBuffer();
  u8g2.drawStr(16, 26, "Connecting to:");
  u8g2.setCursor(16, 42);
  u8g2.print(NetworkName);
  u8g2.sendBuffer();
}

void ConnectedWifi(String NetworkName){
  u8g2.clearBuffer();
  u8g2.drawStr(16, 26, "Connected to:");
  u8g2.setCursor(16, 42);
  u8g2.print(NetworkName);
  u8g2.sendBuffer();
}
