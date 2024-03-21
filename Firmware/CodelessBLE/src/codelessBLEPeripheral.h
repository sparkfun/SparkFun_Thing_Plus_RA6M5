#pragma once

#include "codelessBLE.h"
#include <Arduino.h>
#include <cstdint>
#include <stdint.h>

class CodelessPeripheralDevice : public CodelessBase
{
    public:
        /**
         * @brief Constructs a CodelessPeripheralDevice object.
         * 
         * @param serial The UART object to use for communication.
         */
        CodelessPeripheralDevice(UART& serial = Serial2) : CodelessBase(serial)
        {
        }

        /**
         * @brief Sets up the default configuration for the peripheral device.
         * 
         * @return true if the setup is successful, false otherwise.
         */
        virtual bool setupDefault(void) override
        {
            bool retval = false;
            
            if(_connected)
            {
                reset();

                #ifdef CODELESS_DBG
                Serial.print(sendCommand("AT+ADVSTOP"));
                #else
                sendCommand("AT+ADVSTOP");
                #endif

                #ifdef CODELESS_DBG
                Serial.print(sendCommand("AT+ADVSTART"));
                #else
                sendCommand("AT+ADVSTART");
                #endif

                retval = true;     
            }

            return retval;
        }
};