#include <avr/io.h>
#include "eeprom.h"

namespace EEPROM {

uint8_t Read(uint16_t addr, uint8_t *data) {
    if (addr >= __size__) {
        return Result::RESULT_INVALID_ADDR;
    }

    while(EECR & (1 << EEPE));

    EEARH = (addr & 0xFF00) >> 8;
    EEARL = (addr & 0xFF);

    EECR |= (1 << EERE);

    *data = EEDR;

    return Result::RESULT_OK;
}

static uint8_t Write(uint16_t addr, uint8_t data) {
    if (addr >= __size__) {
        return Result::RESULT_INVALID_ADDR;
    }

    while(EECR & (1 << EEPE));

    EEARH = (addr & 0xFF00) >> 8;
    EEARL = (addr & 0xFF);

    EEDR = data;

    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);

    return Result::RESULT_OK;
}

} // namespace EEPROM
