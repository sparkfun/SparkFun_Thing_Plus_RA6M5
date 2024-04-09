/*
  SerialPassthrough sketch

  Some boards have a USB serial port that operates independently from the
  hardware serial port(s) attached their Digital pins. This means that the
  "serial passthrough" which is possible with the Arduino UNO (commonly used
  to interact with devices/shields that require configuration via serial AT
  commands) will not operate in a similar manner.

  This sketch allows users to emulate the serial passthrough behaviour. (i.e.
  Any text typed in the IDE Serial monitor will be written to the serial port
  oof the Digital pins, and vice-versa.)

  created 23 May 2016
  by Erik Nyquist

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialPassthrough


  This sketch has been modified for the SparkFun Ting Plus - RA6M5. "Serial"
  refers to the USB Serial port attached to the Serial Monitor, and "Serial2"
  refers to the hardware serial port attached to pins D31 and D32; for the
  DA14531MOD Bluetooth module. This sketch will emulate Serial passthrough
  for those two Serial ports on the bSparkFun Ting Plus - RA6M5. The default
  communication settings for the DA14531MOD are:
  
  BaudRate : 57600
  DataBits : 8
  StopBits : 1
  Parity : None
  Flow Control : None
  Transmit Text: Append CR

  Modified 18 March 2024
  by SparkFun Electronics
  author: Wes F

*/

void setup() {
  Serial.begin(57600);
  Serial2.begin(57600);
}

void loop() {
  if (Serial.available()) {        // If anything comes in Serial (USB),
    Serial2.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)
  }

  if (Serial2.available()) {       // If anything comes in Serial1 (pins 0 & 1)
    Serial.write(Serial2.read());  // read it and send it out Serial (USB)
  }
}
