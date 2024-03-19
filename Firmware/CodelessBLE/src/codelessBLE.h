#pragma once

#include <Arduino.h>
#include <cstdint>
#include <stdint.h>

// Uncomment if you want to enable debug messages
// #define CODELESS_DBG
// Uncomment if you want to use the codeless data pump binary. CURRENTLY UNSUPPORTED.
// #define CODELESS_DATA_PUMP

#define DEFAULT_CODELESS_BAUD_RATE 57600
#define DEFAULT_TIMEOUT_IN_S 2

/**
 * @brief The CodelessStatus enum represents the status of the CodelessBase class.
 */
typedef enum
{
    CODELESS_OK,
    CODELESS_ERROR
} CodelessStatus;

/**
 * @brief The CodelessAddrType enum represents the address type used by CodelessBase class.
 */
typedef enum
{
    PUBLIC,
    RANDOM
} CodelessAddrType;

/**
 * @brief The CodelessBase class provides a base implementation for Codeless communication.
 */
class CodelessBase
{
public:
    /**
     * @brief Constructs a CodelessBase object.
     * @param serial The UART object to use for communication.
     */
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

    /**
     * @brief Initializes the CodelessBase object.
     * @param baudRate The baud rate for the serial communication. Default is DEFAULT_CODELESS_BAUD_RATE.
     * @param config The configuration for the serial communication. Default is SERIAL_8N1.
     * @return True if initialization is successful, false otherwise.
     */
    virtual bool begin(uint32_t baudRate = DEFAULT_CODELESS_BAUD_RATE, uint16_t config = SERIAL_8N1);

    /**
     * @brief Deinitializes the CodelessBase object.
     */
    virtual void end(void);

    /**
     * @brief Sends a command to the Codeless device and waits for the response.
     * @param cmd The command to send.
     * @param timeout_in_s The timeout duration in seconds. Default is DEFAULT_TIMEOUT_IN_S.
     * @return The response string from the Codeless device.
     */
    virtual String sendCommand(const String& cmd, const uint16_t timeout_in_s = DEFAULT_TIMEOUT_IN_S);

    /**
     * @brief Reads the output from the Codeless device.
     * @return The output string from the Codeless device.
     */
    virtual String readOutput(void);

    #ifdef CODELESS_DATA_PUMP
    // bool enterBinaryMode(void);
    // bool exitBinaryMode(void);

    // bool sendEscapeSequence(void);
    // bool sendBinaryResume(void);

    // bool binaryMode(void);
    #endif

    /**
     * @brief Checks if the Codeless device is connected.
     * @return True if the device is connected, false otherwise.
     */
    bool connected(void);

    /**
     * @brief Checks the number of bytes available to read from the Codeless device.
     * @return The number of bytes available to read.
     */
    int available(void);

    /**
     * @brief Resets the Codeless device.
     */
    void reset(void);

    /**
     * @brief Sets up the Codeless device with default settings.
     * @return True if setup is successful, false otherwise.
     */
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
