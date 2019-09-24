#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
 
volatile uint16_t rising, falling;
volatile uint32_t counts;
volatile uint32_t dist;
volatile uint16_t us_per_count;
 
ISR(TIMER1_CAPT_vect)
{
	
	if (TCCR1B & (1<<ICES1)) 
	{
		dist=31;
		TCCR1B &= ~(1<<ICES1);
		rising = ICR1;
	}
	else
	{
		TCCR1B |= (1<<ICES1);
		falling = ICR1;
		counts = (uint32_t)falling - (uint32_t)rising;
        dist = (uint32_t)us_per_count * counts * 10 / 58; 
	}
}

ISR(TIMER1_COMPA_vect)
{
	PORTD ^= (1<<PIN5);
	_delay_us(12);
	PORTD ^= (1<<PIN5);
}
 
int main(void)
{
	DDRB |= (1<<PIN0);
	DDRD |= (1<<PIN5);
	
	TCCR1B |= (1<<ICNC1) | (1<<CS10) | (1<<CS11) | (1<<WGM12);
	TIMSK |= (1<<ICIE1) | (1<<OCIE1A); 
	TCCR1B |= (1<<ICES1); 

	OCR1A = 8750;
	
	us_per_count = 8;
	
	sei();
	
	while (1)
	{
		if (dist < 30)
		{
			PORTB |=  (1<<PIN0);
		}else{
			PORTB &= ~(1<<PIN0);
		}	
	}
}