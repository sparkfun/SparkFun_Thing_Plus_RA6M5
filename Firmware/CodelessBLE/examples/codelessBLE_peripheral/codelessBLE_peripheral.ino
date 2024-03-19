/**
 * @file codelessBLE_peripheral.ino
 * @brief This file contains the code for a BLE peripheral device that 
 * communicates with a BME280 sensor.
 * 
 * The code sets up a BLE peripheral device using the CodelessBLEPeripheral 
 * class and establishes a connection with the onboard BLE coprocessor. It 
 * also initializes a BME280 sensor and reads temperature, humidity, and 
 * pressure values from it. The sensor data is then sent to the connected BLE 
 * central device periodically.
 * 
 * The code handles the connection and disconnection events from the BLE device
 * and prints the received data to the Serial monitor.
 * 
 * This code is intended to be used with the SparkFun Thing Plus - RA6M5 
 * development board.
 */
#include <codelessBLEPeripheral.h>
#include <Wire.h>
#include "SparkFunBME280.h"

CodelessPeripheralDevice myBLEPeripheral;
BME280 myBME280;

bool bleConnected = false;
bool reset_loop = false;
uint32_t loop_start_time = 0;
String printstring = "";

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.begin(57600);
    // while(!Serial){delay(100);}; // Uncomment during testing and needing a serial connection.
    Serial.println("Begin BLE Peripheral Demo.");

    #if defined(CODELESS_DBG)
    Serial.println("CODELESS_DBG defined.");
    #endif

    Wire.begin();

    if(!myBME280.beginI2C())
    {
        Serial.println("Sensor didn't respond. Check wiring!");
        while(1);
    }

    Serial.println("Connected to BME280.");

    myBLEPeripheral.connect();
    while(!Serial2){delay(100);};
    Serial.println("Connected to BLE coprocessor.");

    Serial.println("Running default setup routine.");
    myBLEPeripheral.setupDefault();

    Serial.print("Peripheral Device Address: ");
    Serial.print(myBLEPeripheral.sendCommand("AT+BDADDR"));

    Serial.println("Setup complete.");
    digitalWrite(LED_BUILTIN, LOW);
    
    loop_start_time = millis();
}

void loop()
{
    if((loop_start_time - millis()) > 100) // If it's been more than 100ms
    {
        reset_loop = true;
        if(bleConnected)
        {
            digitalWrite(LED_BUILTIN, HIGH);
            printstring = "|"+String(myBME280.readTempC())+","+String(myBME280.readFloatHumidity())+","+String(myBME280.readFloatPressure());
            Serial.print(myBLEPeripheral.sendCommand(printstring));
            digitalWrite(LED_BUILTIN, LOW);
        }

    if (myBLEPeripheral.available()) {       // If anything comes in Serial2 (BLE device)
        String localstring = myBLEPeripheral.readOutput();
        if(!bleConnected)
        {
            if(localstring.endsWith("+CONNECTED\r\n"))
            {
                #ifdef CODELESS_DBG
                Serial.println("[DBG] - outloop - Got connected output.");
                #endif
                bleConnected = true;
            }
        }
        
        if(bleConnected)
        {
            if(localstring.endsWith("+DISCONNECTED\r\n"))
            {
                #ifdef CODELESS_DBG
                Serial.println("[DBG] - outloop - Got disconnected output.");
                #endif
                bleConnected = false;
            }
        }
        Serial.print(localstring);
    }
    if(reset_loop && bleConnected)
    {
        reset_loop = false;
        #ifdef CODELESS_DBG
        Serial.println();
        Serial.println("Resetting loop");
        #endif
        loop_start_time = millis();
    }
}