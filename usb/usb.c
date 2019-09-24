/*
 ATTINY2313 at 11.0592MHZ
 HFUSE=D9
 LFUSE=FF
 EFUSE=FF
 */

#define F_CPU 11059200
#define BAUD 19200

#include
#include
#include

void inituart(void)
{
    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;

    UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << UCSZ1) | (1 << UCSZ0);	
}

void transmitbyte (unsigned char data)
{
    while (!(UCSRA & (1 << UDRE)));	
    UDR = data;
}

int main(void) {
    DDRB |= 1<<PB0;
    inituart();
    while(1) {
        transmitbyte('a');
        _delay_ms(500);
        PORTB ^= 1<<PB0;
    }
    return 0;
}