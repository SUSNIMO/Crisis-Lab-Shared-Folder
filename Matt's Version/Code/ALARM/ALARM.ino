#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <avr/wdt.h>

// Declare pins for the display:
#define TFT_CS     10
#define TFT_RST    9  // You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_DC     8

// Create display:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// Pins connected to the buzzers
const int buzzerPin1 = 2;
const int buzzerPin2 = 3;
const int buzzerPin3 = 4;  
const int buzzerPin4 = 5;
String command = "";
bool Alarm = false;

void displayAlarmTriggered() {
  tft.fillScreen(ST7735_BLACK); // Clear screen with black

  // Display "Tsunami"
  tft.setCursor(0, 0); 
  tft.setTextColor(ST7735_WHITE); 
  tft.setTextSize(3); 
  tft.println("Tsunami");

  // Display "Danger!"
  tft.setCursor(0, 35); 
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(3); 
  tft.println("DANGER!");

  // Draw filled triangle
  tft.fillTriangle(10, 120, 60, 60, 110, 120, ST7735_RED); 

  // Display "Get to higher ground"
  tft.setCursor(0, 150); 
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1); 
  tft.println("Get to higher ground");
}

void displayAlarmNormal() {
  tft.fillScreen(ST7735_BLACK); // Clear screen with black

  // Display "Safe"
  tft.setCursor(0, 0); 
  tft.setTextColor(ST7735_GREEN); 
  tft.setTextSize(5); 
  tft.println("Safe");

  // Display "No tsunami incoming"
  tft.setTextWrap(true);
  tft.setCursor(0, 35); 
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(2); 
  tft.println("No tsunami incoming");
}

void AlarmGo(){
  displayAlarmTriggered();

  //This should last for 20s as the loop runs for 1s and it is being forlooped for 20x
  for (int i = 0; i < 20; i++) {
    // First half of the cycle
    tone(buzzerPin1, 500); 
    tone(buzzerPin2, 750); 
    tone(buzzerPin3, 1500); 
    noTone(buzzerPin4);
    delay(250);             

    noTone(buzzerPin3);    
    tone(buzzerPin4, 2000);
    delay(250);             
    
    noTone(buzzerPin1);     
    noTone(buzzerPin2);    
    tone(buzzerPin3, 1500);
    noTone(buzzerPin4);
    delay(250);             

    noTone(buzzerPin3); 
    tone(buzzerPin4, 2000);
    delay(250);       

    noTone(buzzerPin1);
    noTone(buzzerPin2);
    noTone(buzzerPin3);
    noTone(buzzerPin4);
  }
  displayAlarmNormal(); // Restore normal display after alarm
}

void setup() {
  // Display setup:
  tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);  // Fill screen with black
  tft.setRotation(0);  // Set orientation of the display (0-3)
  tft.setTextWrap(false);  // Disable text wrapping
  
  displayAlarmNormal(); // Show normal alarm message

  // Initialize the buzzer pins as outputs
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(buzzerPin3, OUTPUT);
  pinMode(buzzerPin4, OUTPUT);
  
  // Initialize serial communication at 115200 bits per second
  Serial.begin(115200);
  Serial.println("Restart!"); // Print message to Serial Monitor
}

//Another option for the loop()
/*
void loop() {
  if (Serial.available() > 0) {
    // Read the incoming command
    command = Serial.readStringUntil('\n'); // Read until newline character
    Serial.println(command);
    
    // Check if the command is "Triggered"
    if (command.equals("Triggered")) {
      // Activate the alarm
      AlarmGo();
      Serial.println();
    }
  }
}
*/

//faster version of the loop()
void loop() {

  //when given command from serial port from the esp32 to run alarm it will
  if (Serial.available() > 0) {
    AlarmGo();
    
    //restart the entire arduino
    wdt_enable(WDTO_15MS);
  }
}
