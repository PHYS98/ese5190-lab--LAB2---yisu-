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

void setup() {
	// put your setup code here, to run once:
	//set PIN9-12 and PIN5 as output
	DDRB |= (1<<DDB1);
	DDRB |= (1<<DDB2);
	DDRB |= (1<<DDB3);
	DDRB |= (1<<DDB4);
	DDRB |= (1<<DDB5);
	//Set PIN8 as input
	DDRB &= ~(1<<DDB0);
	//DDRD &= ~(1<<DDD5);
	//Initialize the diode
	PORTB |= (1 << PORTB1);
	PORTB &= ~(1 << PORTB2);
	PORTB &= ~(1 << PORTB3);
	PORTB &= ~(1 << PORTB4);
	PORTB &= ~(1 << PORTB5);

}
int main(void)
{
    /* Replace with your application code */
	//Set PB 1-4(PIN9-12) as output
	setup();
    while (1) 
    {
		//when the switch is pull and red in turn on enter this
		if((PINB & (1<<PINB0))==0 && (PINB & (1<<PINB1))){
			//keep in this loop while the switch is hold
			while((PINB & (1<<PINB0))==0){
				PORTB |= (1 << PORTB5);
			}
			//switch is released
			while((PINB & (1<<PINB0))){
				PORTB |= (1 << PORTB2);
				PORTB &= ~(1 << PORTB1);
				PORTB &= ~(1 << PORTB3);
				PORTB &= ~(1 << PORTB4);
				PORTB &= ~(1 << PORTB5);
			}
		}
		
		else if((PINB & (1<<PINB0))==0 && (PINB & (1<<PINB2))){
			while((PINB  & (1<<PINB0))==0){
				PORTB |= (1 << PORTB5);
			}
			while((PINB & (1<<PINB0 ))){
				PORTB |= (1 << PORTB3);
				PORTB &= ~(1 << PORTB1);
				PORTB &= ~(1 << PORTB2);
				PORTB &= ~(1 << PORTB4);
				PORTB &= ~(1 << PORTB5);
			}
		}
		else if((PINB & (1<<PINB0))==0 && (PINB & (1<<PINB3))){
			while((PINB & (1<<PINB0))==0){
				PORTB |= (1 << PORTB5);
			}
			
			while((PINB & (1<<PINB0))){
				PORTB |= (1 << PORTB4);
				PORTB &= ~(1 << PORTB1);
				PORTB &= ~(1 << PORTB2);
				PORTB &= ~(1 << PORTB3);
				PORTB &= ~(1 << PORTB5);
			}
		}
		else if((PINB & (1<<PINB0))==0 && (PINB & (1<<PINB4))){
			while((PINB & (1<<PINB0))==0){
				PORTB |= (1 << PORTB5);
			}
			while((PINB & (1<<PINB0))){
				PORTB |= (1 << PORTB1);
				PORTB &= ~(1 << PORTB2);
				PORTB &= ~(1 << PORTB3);
				PORTB &= ~(1 << PORTB4);
				PORTB &= ~(1 << PORTB5);
			}
		}
		_delay_ms(100);
    }

}

