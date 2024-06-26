#include <WiFi.h>
#include <esp_now.h>

#define RXp2 16
#define TXp2 17
int LED = 19;

const int bufferSize = 64; // Adjust the buffer size as needed
char buffer[bufferSize];
int bufferIndex = 0;
String data;

//Formatting mac Address
void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength)
{
  snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}

//When a message is recieved... 
//honestly it has no function on this esp32 but eh
//I just added it incase we might need to do something that requires recieving data
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
  Serial.printf("Received message from: %s - %s\n", macStr, buffer);
  // what are our instructions
}

// callback when data is sent
void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status)
{
  char macStr[18];
  formatMacAddress(macAddr, macStr, 18);
  //Serial.print("Last Packet Sent to: ");
  //Serial.println(macStr);
  //Serial.print("Last Packet Send Status: ");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

//Broadcast the Sensor data to the broadcast channel
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
    //Serial.println("Broadcast message success");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_INIT)
  {
    //Serial.println("ESPNOW not Init.");
  }
  else if (result == ESP_ERR_ESPNOW_ARG)
  {
    //Serial.println("Invalid Argument");
  }
  else if (result == ESP_ERR_ESPNOW_INTERNAL)
  {
    //Serial.println("Internal Error");
  }
  else if (result == ESP_ERR_ESPNOW_NO_MEM)
  {
    //Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  }
  else if (result == ESP_ERR_ESPNOW_NOT_FOUND)
  {
    //Serial.println("Peer not found.");
  }
  else
  {
    //Serial.println("Unknown error");
  }
}


void setup() {
  //Serial initialization
  Serial.begin(115200);
  //For listening to the serial port of the arduino uno's sensor
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  //Set device in STA mode to begin with
  WiFi.mode(WIFI_STA);
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
  }

  //initialize bulb (to detect an error in reading messages)
  pinMode(LED, OUTPUT);
}

void loop() {
  // Check if there is data available to read
  while (Serial2.available()) {

    // Read the incoming byte
    char receivedChar = Serial2.read();

    // Check if buffer is not full
    if (bufferIndex < bufferSize - 1) { 
      buffer[bufferIndex++] = receivedChar; // Store the byte in the buffer
      digitalWrite(LED, LOW);
    } 
    
    else {
      // Buffer overflow, handle error or discard data
      Serial.print("Recieved Data is Distorted");
      digitalWrite(LED, HIGH);
    }
  }
  
  // Check if there is data in the buffer
  if (bufferIndex > 0) {

    // Process the data in the buffer
    //message example: S01 - (C): 24.84  (hPa): 0982
    data = "S01 - " + String(buffer);
    processBuffer(data.c_str(), bufferIndex);

    // Clear the buffer after processing
    bufferIndex = 0;
    memset(buffer, 0, bufferSize); // Clear the buffer
  }
}

//Process for sending message to Web esp32
void processBuffer(const char *buffer, int length) {
  Serial.print(buffer);
  broadcast(buffer);
}