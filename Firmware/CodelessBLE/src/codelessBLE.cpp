#include "codelessBLE.h"

void CodelessBase::connect(uint32_t baudRate, uint16_t config)
{
    #ifdef CODELESS_DBG
    Serial.println("[DBG] - Begin connect().");
    #endif
    _serialPort->begin(baudRate, config);

    #ifdef CODELESS_DBG
    if(!_serialPort)
    {
        Serial.println("Could not start serial port.");
    }
    #endif
    _status = CODELESS_OK;
    _connected = true;
}

void CodelessBase::disconnect(void)
{
    #ifdef CODELESS_DBG
    Serial.println("[DBG] - Begin end().");
    #endif
    _serialPort->end();
    _connected = false;
}

String CodelessBase::sendCommand(const String& cmd, const uint16_t timeout_in_s)
{
    #ifdef CODELESS_DBG
    Serial.println("[DBG] - Begin sendCommand().");
    Serial.print("[DBG] - Sending: ");
    Serial.println(cmd);
    #endif

    if(!_serialPort)
    {
        #ifdef CODELESS_DBG
        Serial.println("[DBG] - serial is null! What did you do?!");
        #endif
        return ((String)"");
    }

    uint32_t start_time = millis();
    uint32_t elapsed_time = 0;
    bool reply_expected = true;
    String cmdToWrite = "";

    _reply_string = "";
    _status = CODELESS_ERROR;

    if(_connected)
    {
        if(cmd.startsWith("|"))
        {
            #ifdef CODELESS_DBG
            Serial.println("[DBG] - starts with | - Setting reply_expected to false.");
            #endif
            reply_expected = false;
        }
        if(cmd.endsWith("\r"))
        {
            cmdToWrite = cmd;
        }
        else
        {
            cmdToWrite = cmd+"\r";
        }
        _serialPort->print(cmdToWrite);
        delayMicroseconds(100);
        if(reply_expected)
        {
            _reply_received = false;

            while(!_reply_received)
            {
                if(_serialPort->available())
                {
                    _reply_string+=_serialPort->readString();
                    elapsed_time = millis() - start_time;
                    if(elapsed_time > timeout_in_s*1000)
                    {
                        #ifdef CODELESS_DBG
                        Serial.println("[DBG] - sendCommand - while - Timeout occurred.");
                        Serial.print("[DBG] - sendCommand - while - _reply_string: ");
                        Serial.println(_reply_string);
                        #endif
                        _status = CODELESS_ERROR;
                        return _reply_string;
                    }
                }
                if(_reply_string.endsWith("OK\r\n") || _reply_string.endsWith("ERROR\r\n") || _reply_string.endsWith("+READY\r\n"))
                {
                    _reply_received = true;
                }
                else
                {
                    delayMicroseconds(100);
                    elapsed_time = millis() - start_time;
                    if(elapsed_time > timeout_in_s*1000 )
                    {
                        #ifdef CODELESS_DBG
                        Serial.println("[DBG] - sendCommand - else - Timeout occurred.");
                        Serial.print("[DBG] - sendCommand - else - _reply_string: ");
                        Serial.println(_reply_string);
                        #endif
                        _status = CODELESS_ERROR;
                        return _reply_string;
                    }
                }
            }
        }
        _status = CODELESS_OK;
    }

    return _reply_string;
}

#ifdef CODELESS_DATA_PUMP
// bool CodelessBase::enterBinaryMode()
// {
//     if(_binary_mode)
//     {
//         #ifdef CODELESS_DBG
//         Serial.println("Already in Binary Mode. Returning.");
//         #endif
//         return true;
//     }
//     _binary_mode = true;

//     #ifdef CODELESS_DBG
//     Serial.print(
//     #endif
//     sendCommand("AT+BINREQ")
//     #ifdef CODELESS_DBG
//     )
//     #endif
//     ;

//     return true;
// }

// bool CodelessBase::exitBinaryMode()
// {
//     if(!_binary_mode)
//     {
//         #ifdef CODELESS_DBG
//         Serial.println("Already not in Binary Mode. Returning.");
//         #endif
//         return true;
//     }

//     _binary_mode = false;

//     sendEscapeSequence();

//     #ifdef CODELESS_DBG
//     Serial.print(
//     #endif
//     sendCommand("AT+BINREQEXIT")
//     #ifdef CODELESS_DBG
//     )
//     #endif
//     ;

//     return true;
// }

// bool CodelessBase::sendEscapeSequence()
// {
//     if(!_binary_mode)
//     {
//         #ifdef CODELESS_DBG
//         Serial.println("Can't send escape sequence in command mode. Returning.");
//         #endif
//         return false;
//     }
//     _binary_mode = false;

//     #ifdef CODELESS_DBG
//     Serial.print(
//     #endif
//     sendCommand("+++")
//     #ifdef CODELESS_DBG
//     )
//     #endif
//     ;
//     return true;
// }

// bool CodelessBase::sendBinaryResume()
// {
//     if(_binary_mode)
//     {
//         #ifdef CODELESS_DBG
//         Serial.println("Already in binary mode. Returning.");
//         #endif
//         return false;
//     }
//     _binary_mode = true;

//     #ifdef CODELESS_DBG
//     Serial.print(
//     #endif
//     sendCommand("AT+BINRESUME")
//     #ifdef CODELESS_DBG
//     )
//     #endif
//     ;
//     return true;
// }

// bool CodelessBase::binaryMode()
// {
//     return _binary_mode;
// }
#endif

String CodelessBase::readOutput(void)
{
    _reply_string = "";
    _status = CODELESS_ERROR;

    if(_connected)
    {
        _reply_string = _serialPort->readString();
        _status = CODELESS_OK;
    }

    return _reply_string;
}

bool CodelessBase::connected(void)
{
    if(!_serialPort)
    {
        #ifdef CODELESS_DBG
        Serial.println("[DBG] - connected() - serial is null! What did you do?!");
        #endif
        return false;
    }
    return _connected;
}

int CodelessBase::available(void) 
{   
    if(!_serialPort)
    {
        #ifdef CODELESS_DBG
        Serial.println("[DBG] - available() - serial is null! What did you do?!");
        #endif
        return 0;
    }
    return _serialPort->available(); 
}

bool CodelessBase::setupDefault(void)
{
    reset();
    sendCommand("AT+ADVSTOP");

    return true;
}

void CodelessBase::reset(void)
{
    #ifdef CODELESS_DBG
    Serial.println("[DBG] - Begin reset().");
    Serial.print(
    #endif
    sendCommand("ATR")
    #ifdef CODELESS_DBG
    )
    #endif
    ;
}