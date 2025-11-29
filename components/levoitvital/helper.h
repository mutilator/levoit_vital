
#pragma once

#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <time.h>
#include <sstream>
#include <iomanip>

inline void log_hex(const std::uint8_t *data, int len);
std::uint8_t calculateCommandOrAck(uint8_t *data, std::uint8_t dataLen);
std::vector<uint8_t> generateEfficencyValue(std::uint16_t value);
inline bool checkValChanged(std::uint8_t &value, const char *fieldName, std::uint8_t newValue);
std::uint16_t parse16BitIntegerValue(std::uint8_t high, std::uint8_t low);
inline bool checkValChanged16(std::uint16_t &value, const char *fieldName, std::uint16_t newValue);

/// @brief Creates a string from the incoming status message in hex format to reverse enigneer more data of the protocol.
/// @param data 
/// @param len 
inline void log_hex(const std::uint8_t *data, int len)
{
    char buffer[3 * len + 1]; // 2 Zeichen pro Byte + Leerzeichen + Nullterminator
    char *p = buffer;

    for (int i = 0; i < len; i++)
    {
        sprintf(p, "%02X ", data[i]);
        p += 3; // 2 Zeichen + Leerzeichen
    }
    buffer[3 * len] = '\0'; // Nullterminator

    ESP_LOGD("STATUS", "%s", buffer);
}

/// @brief The levoit vital uses an additive checksum with modulo 256 that is calculated in this method
/// @param data 
/// @param dataLen 
/// @return 
inline std::uint8_t calculateCommandOrAck(std::uint8_t *data, std::uint8_t dataLen)
{
    std::uint16_t sum = 0;
    for (std::uint8_t i = 0; i < dataLen; i++)
    {
        if (i != 5)
            sum += data[i]; // skip the checksum byte
    }
    return (0x1FF - sum) & 0xFF; // 511 - sum, modulo 256
}

/// @brief The "Efficient" value (in the Auto Mode Settings menu) seems to be a value from 100 to 1800 with the factor 1.3. .
/// We can calulate it and add these bytes to the efficency command.
/// @param value
/// @param efficencyValue
inline std::vector<uint8_t> generateEfficencyValue(std::uint16_t value)
{
    std::vector<uint8_t> efficencyValue(4);

    // lock value to min/max
    if (value < 100)
        value = 100;
    if (value > 1800)
        value = 1800;

    // Header
    efficencyValue[0] = 0x03;
    efficencyValue[1] = 0x02;

    // calc raw value (Skalierung 1.3)
    std::uint16_t raw = (std::uint16_t)(value * 1.3 + 0.5); // +0.5 rounding

    // Little Endian
    efficencyValue[2] = raw & 0xFF;        // Low-Byte
    efficencyValue[3] = (raw >> 8) & 0xFF; // High-Byte
    return efficencyValue;
}


inline std::uint16_t parse16BitIntegerValue(std::uint8_t high, std::uint8_t low)
{
    // merge bytes (Little Endian)
    std::uint16_t raw = (uint16_t)high | ((std::uint16_t)low << 8);

    std::uint16_t value = (std::uint16_t)(raw / 1.3 + 0.5);
    return value;
}

/// @brief Simply checks if a value from the incoming status message has changed.
/// @param value 
/// @param fieldName 
/// @param newValue 
/// @return 
inline bool checkValChanged(std::uint8_t &value, const char *fieldName, std::uint8_t newValue)
{
    if (value != newValue)
    {
        value = newValue;
        return true;
    }
    return false;
}

/// @brief Simply checks if a value(16 bit) from the incoming status message has changed.
/// @param value 
/// @param fieldName 
/// @param newValue 
/// @return 
inline bool checkValChanged16(std::uint16_t &value, const char *fieldName, std::uint16_t newValue)
{
    if (value != newValue)
    {
        // ESP_LOGI("CHANGE", "%s was changed to: %u", fieldName, newValue);
        value = newValue;
        return true;
    }
    return false;
}