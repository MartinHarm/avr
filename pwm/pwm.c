#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    unsigned char PWM_val = 3;
    unsigned char up_dn = 0;
    
    DDRB   |= (1 << PB2);          
    TCCR0A = (1 << COM0A1) | (1 << WGM00);
    TCCR0B = (1 << CS01);
    
    while(1)
    {
        if ((PWM_val == 20) || (PWM_val == 3)) {
            up_dn ^= 0x01;
        }
        _delay_ms(17);
        OCR0A  = PWM_val;
        if (up_dn) {
            PWM_val++;
        }
        else {
            PWM_val--;
        }
    }
}