#include <Wire.h>
#include "SparkFun_LPS28DFW_Arduino_Library.h"

// Create a new sensor object
LPS28DFW pressureSensor;

// I2C address selection
uint8_t i2cAddress = LPS28DFW_I2C_ADDRESS_DEFAULT; // 0x5C
//uint8_t i2cAddress = LPS28DFW_I2C_ADDRESS_SECONDARY; // 0x5D

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("LPS28DFW Example 1 - Basic Readings!");

    // Initialize the I2C library
    Wire.begin();

    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x5C)
    while(pressureSensor.begin(i2cAddress) != LPS28DFW_OK)
    {
        // Not connected, inform user
        //Serial.println("Error: LPS28DFW not connected, check wiring and I2C address!");

        // Wait a bit to see if connection is established
        delay(1000);
    }

    //Serial.println("LPS28DFW connected!");
}

void loop()
{
    // Get measurements from the sensor. This must be called before accessing
    // the pressure data, otherwise it will never update
    pressureSensor.getSensorData();

    // Print temperature
    Serial.print("(C): ");
    Serial.print(pressureSensor.data.heat.deg_c);
    Serial.print("  ");

    // Format the pressure value to ensure it's always 4 digits without the decimal
    char formattedPressure[5]; // 4 digits plus null terminator
    sprintf(formattedPressure, "%04d", (int)pressureSensor.data.pressure.hpa); // Format the pressure value

    // Print the formatted pressure value
    Serial.print("(hPa): ");
    Serial.println(formattedPressure);

    // Only print every second
    //delay(1000);
}
