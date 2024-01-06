#include <avr/io.h>
#include "uart.h"

namespace UART {

void Init(uint16_t ubrr) {
    UBRR0L = static_cast<uint8_t>(ubrr & 0xff);
    UBRR0H = static_cast<uint8_t>(ubrr >> 8);

    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (0<<UMSEL01) | (0<<UMSEL00)|    //Async
             (0<<UPM01)   | (0<<UPM00)  |    //Parity bits
             (1<<USBS0)   |                  //Stop bits
             (0<<UCSZ02)  | (1<<UCSZ01) | (1<<UCSZ00) |  //Set the number of bits.
             (0<<UCPOL0);
}

uint8_t GetChar() {
    while((UCSR0A & (1 << RXC0)) == 0);

    return UDR0;
}

void PutChar(uint8_t data) {
    while((UCSR0A & (1 << UDRE0)) == 0);

    UDR0 = data;
}

bool IsAvailable() {
    return (UCSR0A & (1 << RXC0) == 0);
}

void PutString(char *str) {
    while (*str) {
        PutChar(*str++);
    }
}

} // namespace UART 
