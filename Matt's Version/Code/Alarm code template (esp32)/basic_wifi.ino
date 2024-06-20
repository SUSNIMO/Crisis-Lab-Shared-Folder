#include <WiFi.h>
#include <esp_now.h>

int Sensor;
int Control;
int Alarm;
int dummy;
std::string pressure_data = "";
std::string threshold_data = "";
float Pressure = 0.00;
float Threshold = 1500.00;
int LED = 2;

void alarm_trig(){
  digitalWrite(LED, HIGH);
}

void SensorRead(const char *data) {
  pressure_data = std::string(data).substr(25, 4);
  Pressure = std::stof(pressure_data);
  //Serial.println(Pressure);
}

void ControlRead(const char *data) {
  threshold_data = std::string(data).substr(13, 4);
  Threshold = std::stof(threshold_data);
  //Serial.println(Threshold);
}

void Find(std::string text, int& ID, std::string search, int start, int length) {
  ID = text.find(search.c_str(), start, length);
  if (ID != std::string::npos) {
    ID = 1; 
  } else {
    ID = 0; 
  }
}

void verifyData(std::string message) {
  // message example: S01 - (C): 24.84  (hPa): 0982
  // message example: C01 - (hPa): 1000
  Find(message, Sensor, "S", 0, 1);
  Find(message, Control, "C", 0, 1);
  Find(message, Alarm, "A", 0, 1);
  Find(message, dummy, "01", 1, 2);
  
  if (dummy) {
    if (Sensor) {
      SensorRead(message.c_str());
      Sensor = false;
      Control = false;
      Alarm = false;
    }

    if (Control) {
      ControlRead(message.c_str());
      Sensor = false;
      Control = false;
      Alarm = false;
    }

    if (Alarm) {
      // Alarm logic here
    }
  }
}

void formatMacAddress(const uint8_t *macAddr, char *buffer, int maxLength) {
  snprintf(buffer, maxLength, "%02x:%02x:%02x:%02x:%02x:%02x", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}

void receiveCallback(const uint8_t *macAddr, const uint8_t *data, int dataLen) {
  // only allow a maximum of 250 characters in the message + a null terminating byte
  char buffer[ESP_NOW_MAX_DATA_LEN + 1];
  int msgLen = min(ESP_NOW_MAX_DATA_LEN, dataLen);
  strncpy(buffer, (const char *)data, msgLen);
  // make sure we are null terminated
  buffer[msgLen] = 0;
  // format the mac address
  // char macStr[18];
  // formatMacAddress(macAddr, macStr, 18);
  // debug log the message to the serial port
  // Serial.print("Received message from: ");
  // Serial.println(macStr);
  // Serial.print("Message: ");
  // Serial.println(buffer);
  // process the received message
  //Serial.println(buffer);
  verifyData(buffer);
}

// callback when data is sent
void sentCallback(const uint8_t *macAddr, esp_now_send_status_t status) {
  // char macStr[18];
  // formatMacAddress(macAddr, macStr, 18);
  // Serial.print("Last Packet Sent to: ");
  // Serial.println(macStr);
  // Serial.print("Last Packet Send Status: ");
  // Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void broadcast(const String &message) {
  // this will broadcast a message to everyone in range
  uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  esp_err_t result = esp_now_send(broadcastAddress, (const uint8_t *)message.c_str(), message.length());
  
  if (result == ESP_OK) {
    // Serial.println("Broadcast message success");
  } else if (result == ESP_ERR_ESPNOW_NOT_INIT) {
    // Serial.println("ESPNOW not Init.");
  } else if (result == ESP_ERR_ESPNOW_ARG) {
    // Serial.println("Invalid Argument");
  } else if (result == ESP_ERR_ESPNOW_INTERNAL) {
    // Serial.println("Internal Error");
  } else if (result == ESP_ERR_ESPNOW_NO_MEM) {
    // Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  } else if (result == ESP_ERR_ESPNOW_NOT_FOUND) {
    // Serial.println("Peer not found.");
  } else {
    // Serial.println("Unknown error");
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  // Serial.println("ESPNow Example");
  // Output my MAC address - useful for later
  // Serial.print("My MAC Address is: ");
  // Serial.println(WiFi.macAddress());
  // shut down wifi
  WiFi.disconnect();
  // startup ESP Now
  if (esp_now_init() == ESP_OK) {
    // Serial.println("ESPNow Init Success");
    esp_now_register_recv_cb(receiveCallback);
    esp_now_register_send_cb(sentCallback);
  } else {
    // Serial.println("ESPNow Init Failed");
    delay(3000);
    ESP.restart();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Pressure > Threshold){
    // alarm triggers
    broadcast("A01 - 1");
    Serial.println("Triggered");
    Serial.println("Triggered");
    Serial.println("Triggered");
    Serial.println("Triggered");
    Serial.println("Triggered");
    Serial.println("Triggered");
  } else {
    digitalWrite(LED, LOW);
    broadcast("A01 - 0");
    //Serial.println("Not Triggered");
  }
}
