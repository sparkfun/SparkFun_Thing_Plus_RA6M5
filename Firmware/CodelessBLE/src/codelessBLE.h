#pragma once

#include <Arduino.h>
#include <cstdint>
#include <stdint.h>

// #define CODELESS_DBG
// #define CODELESS_DATA_PUMP

typedef enum
{
    CODELESS_OK,
    CODELESS_ERROR
} CodelessStatus;

typedef enum
{
    PUBLIC,
    RANDOM
} CodelessAddrType;

class CodelessBase
{
    public:
        #ifdef CODELESS_DATA_PUMP
        CodelessBase(UART& serial = Serial2) : _serialPort{&serial},
                                                _connected{false},
                                                _reply_received{false},
                                                _binary_mode{false},
                                                _status{CODELESS_ERROR},
                                                _reply_string{""}
        {
        }
        #else
        CodelessBase(UART& serial = Serial2) : _serialPort{&serial},
                                                _connected{false},
                                                _reply_received{false},
                                                _status{CODELESS_ERROR},
                                                _reply_string{""}
        {
        }
        #endif

        virtual void connect(uint32_t baudRate = 57600, uint16_t config = SERIAL_8N1);
        virtual void disconnect(void);

        virtual String sendCommand(const String& cmd, const uint16_t timeout_in_s = 2);
        virtual String readOutput(void);

        #ifdef CODELESS_DATA_PUMP
        // bool enterBinaryMode(void);
        // bool exitBinaryMode(void);

        // bool sendEscapeSequence(void);
        // bool sendBinaryResume(void);

        // bool binaryMode(void);
        #endif

        bool connected(void);

        int available(void);

        void reset(void);

        virtual bool setupDefault(void);

    protected:
        bool _connected;
        bool _reply_received;
        CodelessStatus _status;
        
        String _reply_string;

        UART* _serialPort;

        #ifdef CODELESS_DATA_PUMP
        bool _binary_mode;
        // const String[12] unsolicited_str = {"\r\n+READY\r\n",
        //                                     "\r\n+AWAKE\r\n",
        //                                     "\r\n+CONNECTED\r\n",
        //                                     "\r\n+DISCONNECTED\r\n",
        //                                     "\r\n+BONDING SUCCESS\r\n",
        //                                     "\r\n+PASSCODE REQ RECEIVED\r\n",
        //                                     "\r\n+SECURITY REQ. AUTH LEVEL: ",
        //                                     "\r\n+BINARY MODE SUPPORTED\r\n",
        //                                     "\r\n+COMMAND MODE SUPPORTED\r\n",
        //                                     "\r\n+ECHO ON\r\n",
        //                                     "\r\n+ECHO OFF\r\n",
        //                                     "\r\n+ESC SEQ\r\n"};

        // const String[4] bin_unsolicited_str = {"\r\n+BINREQ\r\n\r\n",
        //                                        "\r\n+BINREQACK\r\n\r\n",
        //                                        "\r\n+BINREQEXITACK\r\n\r\n",
        //                                        "\r\n+BINREQEXIT\r\n\r\n"};
        #endif

};