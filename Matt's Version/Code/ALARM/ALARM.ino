// Pins connected to the buzzers
const int buzzerPin1 = 2;
const int buzzerPin2 = 3;
const int buzzerPin3 = 4;  
const int buzzerPin4 = 5;
bool Alarm = false;

void AlarmGo(){
  for (int i = 0; i < 20; i++) { // Repeat the alert sound 10 times

    // First half of the cycle
    tone(buzzerPin1, 500); // Send a 1kHz sound wave to the first buzzer
    tone(buzzerPin2, 750); // Send a 1kHz sound wave to the second buzzer
    tone(buzzerPin3, 1500); // Send a 1.5kHz sound wave to the third buzzer
    noTone(buzzerPin4);
    delay(250);             // Delay for 125 milliseconds

    noTone(buzzerPin3);     // Stop the third buzzer (halfway point)
    tone(buzzerPin4, 2000);
    delay(250);             // Delay for another 125 milliseconds
    
    noTone(buzzerPin1);     // Stop the first buzzer
    noTone(buzzerPin2);     // Stop the second buzzer
    tone(buzzerPin3, 1500);
    noTone(buzzerPin4);
    delay(250);             // Delay for 250 milliseconds

    noTone(buzzerPin3); // Send a 1.5kHz sound wave to the third buzzer
    tone(buzzerPin4, 2000);
    delay(250);             // Delay for 125 milliseconds

    noTone(buzzerPin1);
    noTone(buzzerPin2);
    noTone(buzzerPin3);
    noTone(buzzerPin4);
  }
}

void setup() {
  // Initialize the buzzer pins as outputs
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(buzzerPin3, OUTPUT);
  pinMode(buzzerPin4, OUTPUT);
  
  // Initialize serial communication at 9600 bits per second
  Serial.begin(115200);
  Serial.print("Restart!");
}

void loop() {
  //Serial.println("HI");
  // Check if data is available to read from the serial port
  if (Serial.available() > 0) {
    Alarm = true;
    if (Alarm){
      AlarmGo();
    }
    Alarm = false;
  }

}

/*

// Pins connected to the buzzers
const int buzzerPin1 = 2;
const int buzzerPin2 = 3;
const int buzzerPin3 = 4;  
const int buzzerPin4 = 5;

void AlarmGo(){
  for (int i = 0; i < 20; i++) { // Repeat the alert sound 10 times

    // First half of the cycle
    tone(buzzerPin1, 500); // Send a 1kHz sound wave to the first buzzer
    tone(buzzerPin2, 750); // Send a 1kHz sound wave to the second buzzer
    tone(buzzerPin3, 1500); // Send a 1.5kHz sound wave to the third buzzer
    noTone(buzzerPin4);
    delay(250);             // Delay for 125 milliseconds

    noTone(buzzerPin3);     // Stop the third buzzer (halfway point)
    tone(buzzerPin4, 2000);
    delay(250);             // Delay for another 125 milliseconds
    
    noTone(buzzerPin1);     // Stop the first buzzer
    noTone(buzzerPin2);     // Stop the second buzzer
    tone(buzzerPin3, 1500);
    noTone(buzzerPin4);
    delay(250);             // Delay for 250 milliseconds

    noTone(buzzerPin3); // Send a 1.5kHz sound wave to the third buzzer
    tone(buzzerPin4, 2000);
    delay(250);             // Delay for 125 milliseconds

    noTone(buzzerPin1);
    noTone(buzzerPin2);
    noTone(buzzerPin3);
    noTone(buzzerPin4);
  }
}

void setup() {
  // Initialize the buzzer pins as outputs
  pinMode(buzzerPin1, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);
  pinMode(buzzerPin3, OUTPUT);
}

void loop() {
  AlarmGo();
  delay(5000);
}

*/