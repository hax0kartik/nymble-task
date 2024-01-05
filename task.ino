#include "uart.h"
#include "eeprom.h"

int main() {
    const uint32_t fosc = 16000000UL;
    const uint16_t baud = 2400;

    constexpr uint16_t ubrr = UART::calcUbrr(baud, fosc);
    UART::Init(ubrr);
    
    while(1) {
        uint8_t c = 0;
        int idx = 0;

        do {
          c = UART::GetChar();
          int err = EEPROM::Write(idx, c);
          idx++;
        } while (c != '\n');

        for (int i = 0; i < idx; i++) {
          EEPROM::Read(i, &c);
          UART::PutChar(c);
        }    
    }

  return 0;
}
