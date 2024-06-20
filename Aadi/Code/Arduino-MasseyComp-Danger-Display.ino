

ST7735 TFT SPI display pins for Arduino Uno/Nano:
 * LED =   3.3V
 * SCK =   13
 * SDA =   11
 * A0 =    8
 * RESET = 9
 * CS =    10
 * GND =   GND
 * VCC =   5V

Another version marked as KMR-1.8 SPI:
This version only supports 3.3V logic so put a level shifter for all I/O pins, or a 2.2k resistor between
the display and arduino, and a 3.3k resistor to ground to create a simple voltage divider to produce a 3V output.
 * LED- =  GND
 * LED+ =  15Ω resistor to 5V
 * CS =    10
 * SCL =   13
 * SDA =   11
 * A0  =   8
 * RESET = 9
 * VCC =   5V or 3.3V (the display has it's own 3.3V regulator)
 * GND =   GND

Hardware SPI Pins:
 * Arduino Uno   SCK=13, SDA=11
 * Arduino Nano  SCK=13, SDA=11
 * Arduino Due   SCK=76, SDA=75
 * Arduino Mega  SCK=52, SDA=51

SPI pin names can be confusing. These are the alternative names for the SPI pins:
MOSI = DIN = R/W = SDO = DI = SI = MTSR = SDA = D1 = SDI
CS = CE = RS = SS
DC = A0 = DO = DOUT = SO = MRST
RESET = RST
SCLK = CLK = E = SCK = SCL = D0


Libraries needed:
https://github.com/adafruit/Adafruit-ST7735-Library
https://github.com/adafruit/Adafruit-GFX-Library


Reference page for GFX Library: https://cdn-learn.adafruit.com/downloads/pdf/adafruit-gfx-graphics-library.pdf


Color is expressed in 16 bit with Hexadecimal value.
To select a particular color, go here and copy the "Hexadecimal 16 bit color depth value":
https://ee-programming-notepad.blogspot.com/2016/10/16-bit-color-generator-picker.html

Common colors:
 * BLACK    0x0000
 * BLUE     0x001F
 * RED      0xF800
 * GREEN    0x07E0
 * CYAN     0x07FF
 * MAGENTA  0xF81F
 * YELLOW   0xFFE0
 * WHITE    0xFFFF


#include <Adafruit_GFX.h>  // Include core graphics library
#include <Adafruit_ST7735.h>  // Include Adafruit_ST7735 library to drive the display


// Declare pins for the display:
#define TFT_CS     10
#define TFT_RST    9  // You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_DC     8
// The rest of the pins are pre-selected as the default hardware SPI for Arduino Uno (SCK = 13 and SDA = 11)


// Create display:
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);



#include <Fonts/FreeSerif18pt7b.h>  // Add a custom font





int Variable1;  // Create a variable to have something dynamic to show on the display






void setup()  // Start of setup
{

  // Display setup:

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab

  tft.fillScreen(ST7735_BLACK);  // Fill screen with black

  tft.setRotation(0);  // Set orientation of the display. Values are from 0 to 3. If not declared, orientation would be 0,
                         // which is portrait mode.

  tft.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                           // To override this behavior (so text will run off the right side of the display - useful for
                           // scrolling marquee effects), use setTextWrap(false). The normal wrapping behavior is restored
                           // with setTextWrap(true).




  // We are going to print on the display everything that is static on the setup, to leave the loop free for dynamic elements:

  // Write to the display the text "Tsunami":
  tft.setCursor(0, 0);  // Set position (x,y)
  tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("Tsunami");  // Print a text or value

  
  // Write to the display the text "Danger":
  tft.setCursor(0, 35);  // Set position (x,y)
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(3); // Set color of text. We are using custom font so there is no background color supported
  tft.println("DANGER!");  // Print a text or value


  // Stop using a custom font:
  tft.setFont();  // Reset to standard font, to stop using any custom font previously set


  // Draw filled triangle:
  //tft.fillTriangle(10,120,    60,60,    110,120, ST7735_RED);  // Draw filled triangle (x0,y0,x1,y1,x2,y2,color)


  // Write to the display the text "Get to higher ground":
  tft.setCursor(0, 150);  // Set position (x,y)
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1); // Set color of text. We are using custom font so there is no background color supported
  tft.println("Get to higher ground");  // Print a text or value
  
}  // End of setup







void loop()  // Start of loop
{
  wait(0.2)
  // Draw filled triangle:
  tft.fillTriangle(10,120,    60,60,    110,120, ST7735_RED);  // Draw filled triangle (x0,y0,x1,y1,x2,y2,color)
}  // End of loop
