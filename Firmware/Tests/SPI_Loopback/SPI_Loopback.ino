#include <SPI.h>
#include <cstdint>

void setup()
{
    Serial.begin();
    while(!Serial) {delay(100);};

    Serial.println("SPI loopback test.");

    SPI.begin();
    SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE1));

    testByteTransfer();

    testWordTransfer();
    
    testArrayTransfer();

    SPI.endTransaction();
    SPI.end();
}

void loop()
{

}

void testByteTransfer(void)
{
    const uint8_t testByte = 0b10100011;

    Serial.print("Sending: 0b");
    Serial.println(testByte, BIN);

    uint8_t recvByte = SPI.transfer(testByte);

    Serial.print("Received: 0b");
    Serial.println(recvByte, BIN);

    if (recvByte == testByte)
    {
        Serial.println("Byte loopback successful.");
    }
    else
    {
        Serial.println("Byte loopback unsuccessful. Please check logs.");
    }
}

void testWordTransfer(void)
{
    const uint8_t testWord = 0b1111000010100101;

    Serial.print("Sending: 0b");
    Serial.println(testWord, BIN);

    uint8_t recvWord = SPI.transfer(testWord);

    Serial.print("Received: 0b");
    Serial.println(recvWord, BIN);

    if (recvWord == testWord)
    {
        Serial.println("Word loopback successful.");
    }
    else
    {
        Serial.println("Word loopback unsuccessful. Please check logs.");
    }
}

void testArrayTransfer(void)
{
    const uint8_t numel = 18;

    uint8_t *data = (uint8_t*)malloc(numel);

    uint8_t *data_ptr = data;

    for(uint8_t i = 0; i < numel; ++i)
    {
        *data_ptr++ = i;
    }

    SPI.transfer(data, numel);

    data_ptr = data;

    /* 0 is inital expected results, 255 is when pin is open
     so initialse result variable to 111 to make it clear the value has changed. */
    uint8_t result = 111;

    Serial.println();
    Serial.println("Multiple byte transfer test");
    Serial.println("element value result");

    for(uint8_t i = 0; i< numel; ++i)
    {
        result = *data_ptr++;
        Serial.print(i);
        Serial.print("\t");
        Serial.print(result);
        Serial.print("\t");

        if(result == i)
        {
            Serial.println("pass");
        }
        else
        {
            Serial.println("fail");
        }
    }
}