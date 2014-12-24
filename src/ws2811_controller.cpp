//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#define clockCyclesPerMicrosecond() ( F_CPU / 1000000L )
#define clockCyclesToMicroseconds(a) ( ((a) * 1000L) / (F_CPU / 1000L) )
#define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))


#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h> 
//#include "chasers.hpp"
//#include "flares.hpp"
#include "color_cycle.hpp"


	void example_color_cycle( uint8_t channel);
	volatile static uint16_t in_start = 0;
	volatile static uint8_t in_time  = 0;
	volatile uint16_t timer0_overflow_count = 0;

SIGNAL(TIMER0_OVF_vect)
{
	timer0_overflow_count++;
}

uint16_t micros() {
	uint16_t m;
	uint8_t oldSREG = SREG, t;
	
	cli();
	m = timer0_overflow_count;
	t = TCNT0;

  
	if ((TIFR0 & _BV(TOV0)) && (t < 255))
		m++;

	SREG = oldSREG;
	
	return ((m << 8) + t) * (64 / clockCyclesPerMicrosecond());
}


int main()
{
	static const uint8_t channel = 5;
    DDRB = 0xFF;
	DDRA &= ~(1<<PINA7);
    //flares::flares( channel);
	//	chasers( channel);
	
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS02); //(1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << TOIE0);
	// configure PCINT0 change interrupt

	PCMSK0 |= (1 << PCINT7);
	PCICR |= (1 << PCIE0);
	sei();      // enable interrupts*/

    example_color_cycle(channel);
}
	
void example_color_cycle( uint8_t channel)
{
	using ws2811::rgb;
	rgb leds1[5];
	rgb leds2[5];
	rgb leds3[5];
	rgb leds4[5];
	
	

/*
Red = 0xFF0000
		rgb( 127, 0, 0),
Orange = 0xFFA500
		rgb( 127, 64, 0),
Yellow = 0xFFFF00
		rgb( 127, 100, 0),
Green = 0x008000
		rgb( 0, 64, 0),
Blue = 0x0000FF
		rgb( 0, 0, 127),
Purple = 0x800080
		rgb( 64, 0, 64),
*/

	uint16_t us = 10;
	
	while(1) {
		us = in_time;
		
		color_cycle::flash(false, ws2811::rgb(0,0,0), leds1, channel-2);
		color_cycle::flash(true, ws2811::rgb(25,0,0), leds2, channel-1);
		color_cycle::flash(false, ws2811::rgb(0,25,0), leds3, channel);
		color_cycle::flash(true, ws2811::rgb(0,25,0), leds4, channel+1);
		
		/*
		color_cycle::color_cycle(sequenceAlarm, leds1, channel);
		*/
	}
}
	
// input ppm pin signal change interrupt
ISR(PCINT0_vect)
{
	if (PINA & (1<<PCINT7)) {
		// low->high
		in_start = micros();
	} else {
		// high->low
		in_time = in_start - micros();
	}
}
