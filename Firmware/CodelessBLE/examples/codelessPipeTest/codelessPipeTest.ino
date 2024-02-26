#include <codelessBLECentral.h>

CodelessCentralDevice myBLECentral;

String test = "|123,456,789";
std::vector<String> testvec;

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);

    Serial.begin(57600);
    while(!Serial){delay(100);};
    Serial.println("Begin BLE pipe data test.");

    #if defined(CODELESS_DBG)
    Serial.println("CODELESS_DBG defined.");
    #endif

    myBLECentral.connect();
    while(!Serial2){delay(100);};
    Serial.println("Connected to BLE coprocessor.");

    Serial.println("Running default setup routine.");
    myBLECentral.setupDefault();

    Serial.println("Setup complete. Beginning test.");

    myBLECentral.parsePipeData(test, testvec);

    Serial.print("Parsed: ");
    Serial.println(test);
    Serial.println("Vector became:");
    for(size_t i=0; i<vec.size(); ++i)
    {
        Serial.println(vec[i]);
    }
    Serial.println("End of test. Cue the blinken lights.");
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}