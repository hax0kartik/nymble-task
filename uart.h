#pragma once

namespace UART {

constexpr uint16_t calcUbrr(const uint16_t &baud, const uint32_t &fosc) {
    return ((fosc / 16) / baud) - 1;
}

void Init(uint16_t ubrr);
uint8_t GetChar();
void PutChar(uint8_t data);

// not used in this task -- I used these for debug purposes
void PutString(char *data);
bool IsAvailable();

} // namespace UART
