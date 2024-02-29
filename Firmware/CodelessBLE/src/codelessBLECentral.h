#pragma once

#include "codelessBLE.h"
#include <Arduino.h>
#include <cstdint>
#include <stdint.h>
#include <stdio.h>
#include <vector>

#define MAX_STRING_LENGTH 65535

class CodelessCentralDevice : public CodelessBase
{
    public:
        CodelessCentralDevice(UART& serial = Serial2) : CodelessBase(serial)
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
                sendCommand("AT+CENTRAL")
                #ifdef CODELESS_DBG
                )
                #endif
                ;

                retval = true;     
            }

            return retval;
        }

        bool connectToPeripheral(String& address, CodelessAddrType type = PUBLIC)
        {
            bool retval = false;
            String addrtype = "P";

            if(type == RANDOM)
            {
                addrtype = "R";
            }

            String commandToSend = "AT+GAPCONNECT="+address+","+addrtype;

            if(_connected)
            {
                #ifdef CODELESS_DBG
                Serial.println(
                #endif
                sendCommand(commandToSend)
                #ifdef CODELESS_DBG
                )
                #endif
                ;
                retval = true;
            }

            return retval;
        }

        bool parsePipeData(const String& inputString, std::vector<String>& vec)
        {
            _status = CODELESS_ERROR;
            String rawString = "";

            #ifdef CODELESS_DBG
            Serial.print("[DBG] - parsePipeData() - inputString: ");
            Serial.println(inputString);
            #endif

            if(!vec.empty())
            {
                #ifdef CODELESS_DBG
                Serial.println("[DBG] - parsePipeData() - input vector not empty.");
                #endif
                vec.clear();
            }

            if(inputString.length() > MAX_STRING_LENGTH)
            {
                // if length was 26 and MAX_STRING_LENGTH was 20, truncateLen would be 6
                // if inputString was 'abcdefghijklmnopqrstuvwxyz', then post-truncate
                // inputString would become 'ghijklmnopqrstuvwxyz'.
                #ifdef CODELESS_DBG
                Serial.println("[DBG] - parsePipeData() - String longer than MAX_STRING_LENGTH.");
                Serial.println("[DBG] - parsePipeData() - Losing first part of string.");
                #endif
                uint8_t truncateLen = inputString.length() - MAX_STRING_LENGTH;
                rawString = inputString.substring(truncateLen);
            }
            else
            {
                rawString = inputString;
            }

            #ifdef CODELESS_DBG
            Serial.print("[DBG] - parsePipeData() - rawString: ");
            Serial.println(rawString);
            #endif

            char strBuf[rawString.length()];
            char * tknIdx;

            strcpy(strBuf, rawString.c_str());
            tknIdx = strtok(strBuf, deliminators);

            while(tknIdx != NULL)
            {
                vec.push_back(tknIdx);
                tknIdx = strtok(NULL, deliminators);
            }

            #ifdef CODELESS_DBG
            Serial.println("[DBG] - parsePipeData() - Printing vec");
            Serial.print("[");
            for(size_t i=0; i<vec.size(); ++i)
            {
                if(i!=0)
                {
                    Serial.print(",");
                }
                Serial.print(vec[i]);
            }
            Serial.println("]");
            #endif

            _status = CODELESS_OK;
            return true;
        }

    private:

        static constexpr char deliminators[] = "|,";
};