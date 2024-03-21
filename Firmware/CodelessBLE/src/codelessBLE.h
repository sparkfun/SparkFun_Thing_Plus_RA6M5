#pragma once

#include <Arduino.h>
#include <cstdint>
#include <stdint.h>

// Uncomment if you want to enable debug messages
// #define CODELESS_DBG

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
    CodelessBase(UART& serial = Serial2) : _serialPort{&serial},
                                            _connected{false},
                                            _reply_received{false},
                                            _status{CODELESS_ERROR},
                                            _reply_string{""}
    {
    }

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
};
