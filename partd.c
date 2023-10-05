/*
 * GccApplication5.c
 *
 * Created: 9/30/2023 11:29:35 PM
 * Author : 13777
 */ 
#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "uart.h"


int edge_rise = 0;
int edge_fall = 0;
int unpressed_t =0;
int period = 0;
int rising_edge = 0;
int press = 0;
char String[25];


void setup() {
	// put your setup code here, to run once:
	cli();
	
	UART_init(BAUD_PRESCALER); 
	
	//Set timer1 16MHz / 256
	TCCR1B &= ~(1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |= (1 << CS12);

	//Set timer to CTC
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B |= (1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	OCR1A = 62500; //when count to 62500 back to zero,reset the register
	
	//Enable falling edge control
	TCCR1B &= ~(1 << ICES1);

	TIFR1 |= (1<<ICF1); //clear input capture flag

	//Enable trigger for PINT0
	TIMSK1 |= (1 << ICIE1);
	sei();
}

ISR(TIMER1_CAPT_vect){
	switch(rising_edge){
		case 0:
			edge_fall = ICR1; // take input capture value and save it in falling edge
			TCCR1B |= (1 << ICES1); // set input capture for rising edge back
			rising_edge = 1;     // make rising edge true for next pulse
			press = 1;
			_delay_ms(500);
			break;
			
		case 1:
			edge_rise = ICR1;   // take the input capture value and save it in rising_capture
			TCCR1B &= ~(1 << ICES1); // set input capture for falling edge
			rising_edge = 0;     // make falling_edge variable false so next time it will react to case false
			TIFR1 |= (1<<ICF1); //clear input capture flag
			press = 0;
			period = edge_rise - edge_fall;
			//when overflow happens
			if(period < 0){
				period = 62500 - edge_fall + edge_rise;
			}
			//print dot
			if(1875 < period && period< 12500){
				_delay_ms(500);
				sprintf(String,".");
				UART_putstring(String);
				
			}
		
			//print dash
			else{
				_delay_ms(500);
				sprintf(String,"-");
				UART_putstring(String);	
			}
			break;
	}
	period = 0;
}

int main(void)
{
	setup();
	int t_prev = 0;
    /* Replace with your application code */
    while (1) 
    {
		unpressed_t = 0;
		//button pressed
		if(press){_delay_ms(100);}
		//Button not pressed, measure its time
		else{
			unpressed_t = TCNT1 - t_prev;
			//when overflow happens
			if(unpressed_t < 0){
				unpressed_t = 62500 - t_prev + TCNT1;
			}
			// not pressed for 400 ms
			if(unpressed_t >  25000){
				sprintf(String," ");
				UART_putstring(String);
				t_prev = TCNT1;
				unpressed_t = 0;
			}
		}
    }
}

