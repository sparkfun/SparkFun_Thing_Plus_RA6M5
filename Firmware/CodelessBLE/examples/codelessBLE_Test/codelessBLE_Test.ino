#include <codelessBLE.h>

#include <Arduino.h>

CodelessBase myBLE;

void setup()
{
    Serial.begin(57600);
    while(!Serial){delay(100);};
    Serial.println("Begin BLE Demo.");

    #if defined(CODELESS_DBG)
    Serial.println("CODELESS_DBG defined.");
    #endif

    myBLE.connect();
    while(!Serial2){delay(100);};
    Serial.println("Connected to BLE coprocessor.");

    Serial.println("Running reset routine.");
    myBLE.reset();
    Serial.println("Reset complete.");
    Serial.println("Getting device address...");
    Serial.print(myBLE.sendCommand("AT+BDADDR"));
}

void loop()
{
    if (Serial.available()) {        // If anything comes in Serial (USB),
        Serial.print(myBLE.sendCommand(Serial.readString()));  // read, then command BLE, write response back to Serial.
    }

    if (myBLE.available()) {       // If anything comes in Serial2 (BLE device)
        Serial.print(myBLE.readOutput());  // read it and send it out Serial (USB)
    }
}