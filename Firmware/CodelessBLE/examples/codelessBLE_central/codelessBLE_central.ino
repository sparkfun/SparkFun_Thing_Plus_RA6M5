/**
 * @file codelessBLE_central.ino
 * @brief This file contains the code for a BLE central device that connects to
 * a peripheral device and displays sensor data on an OLED display.
 * 
 * The code sets up a BLE central device using the CodelessBLECentral class. It 
 * establishes a connection with a specific peripheral device, then receives 
 * and displays the data on an OLED display using the SparkFun_Qwiic_OLED 
 * library.
 * 
 * The RA6M5 processor communicates to the BLE coprocessor over a serial 
 * connection. It sends commands to the peripheral device and receives 
 * responses, which are then displayed on the serial monitor. The sensor data 
 * received from the peripheral device is parsed and displayed on the OLED 
 * display.
 * 
 * This code is intended to be used with the SparkFun Thing Plus - RA6M5 
 * development board.
 */

#include <codelessBLECentral.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OLED.h> // https://librarymanager/All#SparkFun_Qwiic_OLED
#include <res/qw_fnt_5x7.h>

CodelessCentralDevice myBLECentral;
QwiicNarrowOLED myOLED;

String peripheralAddress = "48:23:35:34:74:D3"; // Hardware specific, change to your peripheral's address.
String localstring = "";
String printstring_temp = "";
String printstring_hum = "";
String printstring_press = "";

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.begin(DEFAULT_CODELESS_BAUD_RATE);
    // while(!Serial){delay(100);}; // Uncomment during testing and needing a serial connection.
    Serial.println("Begin BLE Central Demo.");

    #if defined(CODELESS_DBG)
    Serial.println("CODELESS_DBG defined.");
    #endif

    Wire.begin();
    if(myOLED.begin() == false)
    {
        Serial.println("Unable to communicate with display. Freezing...");
        while(1);
    }

    Serial.println("Connected to display.");
    myOLED.setFont(QW_FONT_5X7);

    myOLED.erase();

    String hello = "Codeless BLE Demo";

    int x0 = (myOLED.getWidth() - myOLED.getStringWidth(hello)) / 2;
    int y0 = (myOLED.getHeight() - myOLED.getStringHeight("a")) / 2;
    myOLED.text(x0, y0, hello);
    myOLED.display();

    myBLECentral.begin();
    while(!Serial2){delay(100);};
    Serial.println("Connected to BLE coprocessor.");

    Serial.println("Running default setup routine.");
    myBLECentral.setupDefault();

    Serial.print("Central device address: ");
    Serial.print(myBLECentral.sendCommand("AT+BDADDR"));

    myBLECentral.connectToPeripheral(peripheralAddress);

    Serial.println("Setup complete.");
    digitalWrite(LED_BUILTIN, LOW);

    hello = "Wait for conn...";
    x0 = (myOLED.getWidth() - myOLED.getStringWidth(hello)) / 2;
    y0 = (myOLED.getHeight() - myOLED.getStringHeight("a")) / 2;
    myOLED.erase();
    myOLED.text(x0, y0, hello);
    myOLED.display();
}

void loop()
{
    if (Serial.available()) {        // If anything comes in Serial (USB),
        Serial.print(myBLECentral.sendCommand(Serial.readString()));  // read, then command BLE, write response back to Serial.
    }

    if (myBLECentral.available()) {       // If anything comes in Serial2 (BLE device)
        localstring = myBLECentral.readOutput();
        localstring.trim(); // remove leading and trailing \r \n whitespace.
        int16_t index = localstring.indexOf("|");
        
        if(index > -1)
        {
            #ifdef CODELESS_DBG
            Serial.print("[DBG] - loop - readOutput - String contains | at index ");
            Serial.print(index);
            Serial.println(".");
            #endif
            localstring+="\r";
            localstring.remove(index,1);
            String temp = localstring.substring(0,localstring.indexOf(","));
            String hum = localstring.substring(localstring.indexOf(",")+1, localstring.indexOf(",", localstring.indexOf(",")+1));
            String press = localstring.substring(localstring.lastIndexOf(",")+1);
            Serial.print("T: ");
            Serial.print(temp);
            Serial.print(" H: ");
            Serial.print(hum);
            Serial.print(" P: ");
            Serial.println(press);

            printstring_temp = "T: "+temp+" dC";
            int ytemp = (myOLED.getHeight()/3) - myOLED.getStringHeight(printstring_temp);
            printstring_hum = "H: "+hum+" %RH";
            int yhum = (myOLED.getHeight() / 3 * 2) - myOLED.getStringHeight(printstring_hum);
            printstring_press = "P: "+press+" Pa";
            int ypress = myOLED.getHeight() - myOLED.getStringHeight(printstring_press);

            myOLED.erase();
            myOLED.text(3, ytemp, printstring_temp);
            myOLED.display();
            myOLED.text(3, yhum, printstring_hum);
            myOLED.display();
            myOLED.text(3, ypress, printstring_press);
            myOLED.display();
        }
        else
        {
            Serial.println(localstring);
        }
    }
}
