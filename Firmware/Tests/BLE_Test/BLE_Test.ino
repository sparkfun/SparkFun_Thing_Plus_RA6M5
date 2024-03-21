// BLE Test - Use Renesas CODELESS Serial AT Commands from the PC to the device.

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(57600);
    while(!Serial){delay(100);};

    Serial.println("BLE AT Commands Test:");

    Serial2.begin(57600);
    while(!Serial2){delay(100);};

    Serial.println("Began Serial2.");
    Serial.println();
    Serial.println("Please begin sending AT Commands in the following structure.");
    Serial.println("CMD+OPCODE[=VALUE]");
    Serial.println("Not providing a value will often return the current value.");
}

void loop() {
    if (Serial.available()) {        // If anything comes in Serial (USB),
        Serial2.write(Serial.read());  // read it and send it out Serial2 (BLE device)
    }

    if (Serial2.available()) {       // If anything comes in Serial2 (BLE device)
        Serial.write(Serial2.read());  // read it and send it out Serial (USB)
    }
}