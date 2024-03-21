#include "codelessBLE.h"

bool CodelessBase::begin(uint32_t baudRate, uint16_t config)
{
    #ifdef CODELESS_DBG
    Serial.println("[DBG] - Begin begin().");
    #endif
    _serialPort->begin(baudRate, config);

    if(!_serialPort)
    {
        #ifdef CODELESS_DBG
        Serial.println("Could not start serial port.");
        #endif
        _status = CODELESS_ERROR;
        _connected = false;
        return false;
    }

    _status = CODELESS_OK;
    _connected = true;
    
    return true;
}

void CodelessBase::end(void)
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

    if(!_connected)
    {
        #ifdef CODELESS_DBG
        Serial.println("[DBG] - Not connected. Returning.");
        #endif
        return _reply_string;
    }

    // Check if the command is a serial passthrough string
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
    if(!reply_expected)
    {
        _status = CODELESS_OK;
        return _reply_string;
    }
    
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
    _status = CODELESS_OK;

    return _reply_string;
}

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
    Serial.print(sendCommand("ATR"));
    #else
    sendCommand("ATR");
    #endif
}
