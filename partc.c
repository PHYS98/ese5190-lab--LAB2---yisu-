/*
 * GccApplication1.c
 *
 * Created: 9/22/2023 5:19:51 PM
 * Author : 13777
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void setup() {
	// put your setup code here, to run once:
	cli();
	//set PIN9-12 as output
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);

	//Set PIN8 as input
	DDRB &= ~(1<<DDB0);
	//enable internal resistor
	PORTB |= (1<<PORTB0);

	//Initialize the diode
	PORTB |= (1 << PORTB1);
	PORTB &= ~(1 << PORTB2);
	PORTB &= ~(1 << PORTB3);
	PORTB &= ~(1 << PORTB4);
	PORTB &= ~(1 << PORTB5);

	//Set timer1 16MHz
	TCCR1B |= (1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B &= ~(1 << CS12);

	//Set timer to normal
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	
	//Enable falling edge control
	TCCR1B &= ~(1 << ICES1);

	TIFR1 |= (1<<ICF1); //clear input capture flag

	//Enable triggle for PINT0
	TIMSK1 |= (1 << ICIE1);
	sei();
}

ISR(TIMER1_CAPT_vect){
	TIFR1 |= (1<<ICF1); //clear input capture flag
	if((PINB & (1<< PINB0))==0){
		if(PINB & (1<<PINB1)){
			PORTB &= ~(1<<PORTB1);
			PORTB |= (1<<PORTB2);
		}
		if(PINB & (1<<PINB2)){
			PORTB &= ~(1<<PORTB2);
			PORTB |= (1<<PORTB3);
		}
		if(PINB & (1<<PINB3)){
			PORTB &= ~(1<<PORTB3);
			PORTB |= (1<<PORTB4);
		}
		if(PINB & (1<<PINB4)){
			PORTB &= ~(1<<PORTB4);
			PORTB |= (1<<PORTB1);
		}
	}
	_delay_ms(500);

}

int main(void)
{
    /* Replace with your application code */
	setup();
	while(1){
		
	}
	
}



