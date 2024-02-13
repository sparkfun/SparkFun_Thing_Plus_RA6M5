// Test QSPI Flash

#include <Arduino.h>
#include <BlockDevice.h>
#include <QSPIFlashBlockDevice.h>
#include <cstdint>
#include <sys/types.h>

BlockDevice* root = BlockDevice::get_default_instance();

#define QSPIF_SIZE (16 * 1024 * 1024)
#define WRITE_SIZE ( 8 * 1024)

byte w_buffer[WRITE_SIZE];
byte r_buffer[WRITE_SIZE];

void setup()
{
    Serial.begin(115200);
    while(!Serial){delay(100);};

    Serial.println("QSPI Flash Test.");

    int ret = root->init();
    if(ret)
    {
        Serial.println("Error opening QSPIFlash device.");
        while(1){};
    }

    Serial.println("QSPIFlash init complete.");

    randomSeed(analogRead(A0));

}

void loop()
{
    // // Select a random pattern to write flash
    // byte pattern = random(255);

    // // Select a random size for the test buffer
    // int repeat = random(1, WRITE_SIZE);

    // // Select a random start offset
    // int offset = random(0, QSPIF_SIZE - WRITE_SIZE);

    // // Start test
    // erase_write_read_compare(pattern, offset, repeat);

}

void erase_write_read_compare(byte pattern, int offset, int repeat)
{
    Serial.print("Using pattern: ");
    Serial.print(pattern, HEX);
    Serial.print(" ");
    Serial.print(repeat);
    Serial.print(" times starting from ");
    Serial.println(offset, HEX);

    memset(&w_buffer[0], pattern, repeat);

    // Erase flash used for testing
    const uint32_t start_block = (offset / QSPI_ERASE_BLOCK_SIZE);
    const uint32_t end_block = ((offset + repeat) / QSPI_ERASE_BLOCK_SIZE) + 1;
    const uint32_t erase_size = (end_block - start_block) * QSPI_ERASE_BLOCK_SIZE;
    const uint32_t erase_addr = (start_block) * QSPI_ERASE_BLOCK_SIZE;
    root->erase(erase_addr, erase_size);

    // Write pattern
    root->program(&w_buffer[0], offset, repeat);

    // Read back
    root->read(&r_buffer[0], offset, repeat);

    // Compare
    if(memcmp(&w_buffer[0], &r_buffer[0], repeat))
    {
        Serial.println("Error comparing buffers, dumping content...");
        Serial.println("Write buffer:");
        dump_buffer(&w_buffer[0], repeat);
        Serial.println("Read buffer:");
        dump_buffer(&r_buffer[0], repeat);
        while(1){}
    }
    delay(5);
}

void dump_buffer(uint8_t *b, uint32_t len)
{
    if(b != nullptr)
    {
        Serial.println("");
        for( int i = 0; i < len; i++)
        {
            if(i != 0 && i % 32 == 0)
            {
                if(i != 0)
                {
                    Serial.println();
                }
            }
            Serial.print(*(b + i) >>   4, HEX);
            Serial.print(*(b + i) & 0x0F, HEX);
        }
        Serial.println();
        Serial.println("");
    }
}
