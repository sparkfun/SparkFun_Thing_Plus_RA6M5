// BLE Test - Use Renesas CODELESS Serial AT Commands from the PC to the device.

void setup() {

    Serial.begin(57600);
    while(!Serial){delay(100);};

    Serial.println("BLE AT Commands Test:");

    Serial1.begin(57600);
    while(!Serial1){delay(100);};

    Serial.println("Began Serial1.");
    Serial.println();
    Serial.println("Please begin sending AT Commands in the following structure.");
    Serial.println("CMD+OPCODE[=VALUE]");
    Serial.println("Not providing a value will return the current value.");
}

void loop() {
    if (Serial.available()) {        // If anything comes in Serial (USB),
        Serial1.write(Serial.read());  // read it and send it out Serial1 (pins 0 & 1)
    }

    if (Serial1.available()) {       // If anything comes in Serial1 (pins 0 & 1)
        Serial.write(Serial1.read());  // read it and send it out Serial (USB)
    }
}