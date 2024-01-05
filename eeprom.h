#pragma once

namespace EEPROM {

const uint16_t __size__ = 1024;

enum Result : uint8_t {
    RESULT_OK = 0,
    RESULT_INVALID_ADDR = 1
};

uint8_t Read(uint16_t addr, uint8_t *data);
uint8_t Write(uint16_t addr, uint8_t data);
    
} // namespace EEPROM
