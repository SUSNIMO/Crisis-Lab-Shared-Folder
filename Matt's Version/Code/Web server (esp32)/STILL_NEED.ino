#include <WiFi.h>
#include <esp_now.h>
#include <WebServer.h>  
#include "SuperMon.h"   // .h file that stores your html page code

//#define USE_INTRANET //comment this out if you want it to turn into a AP

// "Login" for esp32 to connect to a wifi
#define LOCAL_SSID "ZION"
#define LOCAL_PASS "largeocean922"

// "Login" ofr devices to connect to the Esp32
#define AP_SSID "System Command"
#define AP_PASS "password123"

//DATA
int Sensor;
int Control;
int Alarm;
int dummy;

std::string pressure_data;
std::string temp_data;

char XML[2048];
char buf[32];

// variable for the IP reported when you connect to your homes intranet (during debug mode)
IPAddress Actual_IP;

// definitions of your desired intranet created by the ESP32
IPAddress PageIP(192, 168, 1, 1); //IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;

// gotta create a server
WebServer server(80);

// Just a function for finding something in a string
void Find(std::string text, int& ID, std::string search, int start, int length)
{
  ID = text.find(search.c_str(), start, length);
  if (ID != std::string::npos) {
        ID = 1; 
    } else {
        ID = 0; 
    }
}

//Store the data in temp_data var
//(C): 24.84  (hPa): 0982
void temp(const char *data)
{
  temp_data = std::string(data).substr(11, 2);
}

//Store the data in pressure_data var
//(C): 24.84  (hPa): 0982
void pressure(const char *data)
{
  pressure_data = std::string(data).substr(25, 4);
}

//Verify data recieved from Broadcast channel
void verifyData(std::string message){
  //message example for sensor message: S01 - (C): 24.84  (hPa): 0982
  //message example for computer: C01 - (hPa): 0982

  //Search ID (incase we don't get random messages from esp32 outside the system)
  Find(message, Sensor, "S", 0, 1);
  Find(message, Control, "C", 0, 1);
  Find(message, Alarm, "A", 0, 1);
  Find(message, dummy, "01", 1, 2);
  
  //Sort the message to their respective functions
  if (dummy){
    if (Sensor){
      temp(message.c_str());
      pressure(message.c_str());
    }
  }
}

//Formatting Mac Address
void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength)
{
  snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}

//Function for when a message is recieved from the broadcast channel
void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen)
{
  // only allow a maximum of 250 characters in the message + a null terminating byte
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];
  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);  
  strncpy(buffer, (const char *)data, msgLen);
  // make sure we are null terminated
  buffer[msgLen] = 0;
  // format the mac address
  char macStr[18];
  formatMacAddress(macAddr, macStr, 18);
  // debug log the message to the serial port
  //Serial.printf("Received message from: %s - %s\n", macStr, buffer);
  // what are our instructions
  //Serial.print(buffer);

  //Verify data
  verifyData(buffer);
}

// callback when data is sent to check if data has been recieved
void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status)
{
  char macStr[18];
  formatMacAddress(macAddr, macStr, 18);
  Serial.print("Last Packet Sent to: ");
  Serial.println(macStr);
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//function to when you send message to the broadcast channel
void broadcast(const String &message)
{
  // this will broadcast a message to everyone in range
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, broadcastAddress, 6);
  if (!esp_now_is_peer_exist(broadcastAddress))
  {
    esp_now_add_peer(&peerInfo);
  }
  esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
  // and this will send a message to a specific device
  /*uint8_t peerAddress[] = {0x3C, 0x71, 0xBF, 0x47, 0xA5, 0xC0};
  esp_now_peer_info_t peerInfo = {};
  memcpy(&peerInfo.peer_addr, peerAddress, 6);
  if (!esp_now_is_peer_exist(peerAddress))
  {
    esp_now_add_peer(&peerInfo);
  }
  esp_err_t result = esp_now_send(peerAddress, (const uint8_t *)message.c_str(), message.length());*/
  if (result == ESP_OK)
  {
    Serial.println("Broadcast message success");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_INIT)
  {
    Serial.println("ESPNOW not Init.");
  }
  else if (result == ESP_ERR_ESPNOW_ARG)
  {
    Serial.println("Invalid Argument");
  }
  else if (result == ESP_ERR_ESPNOW_INTERNAL)
  {
    Serial.println("Internal Error");
  }
  else if (result == ESP_ERR_ESPNOW_NO_MEM)
  {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
  {
    Serial.println("Peer not found.");
  }
  else
  {
    Serial.println("Unknown error");
  }
}

void setup() {
  //Serial initialization
  Serial.begin(115200);
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);

  //print Startup data
  Serial.println("ESPNow Example");
  // Output my MAC address - useful for later
  Serial.print("My MAC Address is: ");
  Serial.println(WiFi.macAddress());

  // shut down wifi
  WiFi.disconnect();

  // startup ESP Now
  if (esp_now_init() == ESP_OK)
  {
    Serial.println("ESPNow Init Success");
    esp_now_register_recv_cb(receiveCallback);
    esp_now_register_send_cb(sentCallback);
  }
  else
  {
    Serial.println("ESPNow Init Failed");
    delay(3000);
    ESP.restart();

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  }

  // if your web page or XML are large, you may not get a call back from the web page
  // and the ESP will think something has locked up and reboot the ESP
  // not sure I like this feature, actually I kinda hate it
  // disable watch dog timer 0
  disableCore0WDT();

  // maybe disable watch dog timer 1 if needed
  //  disableCore1WDT();

  // just an update to progress

  Serial.println("starting server");

  // if you have this #define USE_INTRANET,  you will connect to your home intranet, again makes debugging easier
#ifdef USE_INTRANET
  WiFi.begin(LOCAL_SSID, LOCAL_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  Actual_IP = WiFi.localIP();
#endif

  // if you don't have #define USE_INTRANET, here's where you will creat and access point
  // an intranet with no internet connection. But Clients can connect to your intranet and see
  // the web page you are about to serve up
#ifndef USE_INTRANET
  WiFi.softAP(AP_SSID, AP_PASS);
  delay(100);
  WiFi.softAPConfig(PageIP, gateway, subnet);
  delay(100);
  Actual_IP = WiFi.softAPIP();
  Serial.print("IP address: "); Serial.println(Actual_IP);
#endif

  printWifiStatus();


  // these calls will handle data coming back from your web page
  // this one is a page request, upon ESP getting / string the web page will be sent
  server.on("/", SendWebsite);

  // upon esp getting /XML string, ESP will build and send the XML, this is how we refresh
  // just parts of the web page
  server.on("/xml", SendXML);

  server.on("/UPDATE_THRESHOLD", UpdateThreshold);
  // finally begin the server
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

// I think I got this code from the wifi example
void printWifiStatus() {

  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("Open http://");
  Serial.println(ip);
}


// code to send the main web page
// PAGE_MAIN is a large char defined in SuperMon.h
void SendWebsite() {

  Serial.println("sending web page");
  // you may have to play with this value, big pages need more porcessing time, and hence
  // a longer timeout that 200 ms
  server.send(200, "text/html", PAGE_MAIN);

}

//function to broadcast and process the threshold data that was updated by the web
void UpdateThreshold() {
  // Get the value of the "VALUE" parameter from the request
  String Tdata = server.arg("VALUE");

  // Convert the String to an integer
  int ThresholdValue = Tdata.toInt();

  // Convert the integer to a String explicitly
  String Threshold = "C01 - (hPa): " + String(ThresholdValue);

  // Debug print the Threshold value
  Serial.print("UpdateThreshold: ");
  Serial.println(Threshold);

  // Broadcast the Threshold value (assuming you have the broadcast function set up properly)
  broadcast(Threshold);

  // Send an empty response to the client
  server.send(200, "text/plain", "");
}

// code to send the main web page
void SendXML() {

  // Serial.println("sending xml");

  strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

  sprintf(buf, "<Pressure>%s</Pressure>\n", pressure_data.c_str());
  strcat(XML, buf);

  sprintf(buf, "<Temperature>%s</Temperature>\n", temp_data.c_str());
  strcat(XML, buf);

  strcat(XML, "</Data>\n");
  
  //print the result above
  Serial.println(XML);

  server.send(200, "text/xml", XML);


}


// end of code