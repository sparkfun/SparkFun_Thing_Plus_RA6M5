#pragma once

#include "codelessBLE.h"
#include <Arduino.h>
#include <cstdint>
#include <stdint.h>

class CodelessPeripheralDevice : public CodelessBase
{
    public:
        CodelessPeripheralDevice(UART& serial = Serial2) : CodelessBase(serial)
        {
        }

        virtual bool setupDefault(void) override
        {
            bool retval = false;
            
            if(_connected)
            {
                reset();

                #ifdef CODELESS_DBG
                Serial.println(
                #endif
                sendCommand("AT+ADVSTOP")
                #ifdef CODELESS_DBG
                )
                #endif
                ;

                #ifdef CODELESS_DBG
                Serial.println(
                #endif
                sendCommand("AT+ADVSTART")
                #ifdef CODELESS_DBG
                )
                #endif
                ;


                retval = true;     
            }

            return retval;
        }
};