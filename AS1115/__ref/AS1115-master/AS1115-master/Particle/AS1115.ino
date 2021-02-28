// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AS1115
// This code is designed to work with the AS1115_I2CL_3CE I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/LED-Display?sku=AS1115_I2CL_3CE#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// AS1115 I2C address is 0x00(00)
#define Addr 0x00

int digit, data;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "AS1115");
  Particle.variable("data", data);

  // Initialise I2C communication as Master
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Shutdown register
  Wire.write(0x0C);
  // Normal Operation, Reset Feature Register to Default Settings
  Wire.write(0x01);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Intensity Control Register
  Wire.write(0x0A);
  // Duty cycle = 1/16
  Wire.write(0x80);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Feature Register
  Wire.write(0x0E);
  // Enable HEX decoding
  Wire.write(0x04);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Scan-limit Register
  Wire.write(0x0B);
  // Display digits 0-2
  Wire.write(0x02);
  // Stop I2C transmission
  Wire.endTransmission();

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select Decode-enable Register
  Wire.write(0x09);
  // Set all digits to font decode.
  Wire.write(0x07);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  for (data = 0; data <= 0x10; data++)
  {
    for (digit = 0; digit <= 2; digit++)
    {
      // Start I2C transmission
      Wire.beginTransmission(Addr);
      // Select digits
      Wire.write(digit + 1);
      // Write data on digits
      Wire.write(data);
      // Stop I2C transmission
      Wire.endTransmission();
    }
    // Output to dashboard
    Particle.publish("Display on 7-segment : ", String(data));
    delay(1000);
  }
}
