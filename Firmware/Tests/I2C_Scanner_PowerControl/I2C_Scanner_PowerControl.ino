/*
 This example also the Fuel Gauge IC at address 0x36.
 */
#include <Wire.h>

void setup()
{
  Serial.begin(115200);
  while(!Serial){delay(100);};
  Serial.println();
  Serial.println("I2C Scanner");

  Wire.begin();
}

void loop()
{
  Serial.println();
  for (byte address = 1; address < 127; address++ )
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Device found at address 0x");
      if (address < 0x10)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  Serial.println("Done");
  delay(100);
}
