//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <avr/io.h>
#include <math.h>
#include <util/delay.h>
#include <stdlib.h>
#include <avr/interrupt.h> 
#include "ws2811_8.h"
#include "plane.hpp"


volatile static uint16_t in_start = 0;
volatile static uint16_t in_time  = 0;
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
	
	return ((m << 8) + t) * 8;
}

int main()
{
	static const uint8_t channel = 5;
	static const uint8_t led_count = 15;
	ws2811::rgb leftLED[led_count];
	ws2811::rgb rightLED[led_count];
	ws2811::rgb markerLED[6];
	
	//define red left light, green right light, tail white strobe, body red beacon top and bottom 
		
    DDRB = 0xFF;
	DDRA &= ~(1<<PINA7);
	DDRA &= ~(1<<PINA6);
	
	//TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	TIMSK0 |= (1 << TOIE0);

	// configure PCINT0 change interrupt
	PCMSK0 |= (1 << PCINT7);
	PCICR |= (1 << PCIE0);
	sei();      // enable interrupts*/

	uint8_t us = 00;
	bool alarm = false;
	uint8_t count = 0;
	while(1)
	{
		cli();
		us = (in_time - 450) / 105;
		sei();
		
		alarm = (bool)(PINA & (1 << PINA6));
		
		plane::flash(alarm, us, leftLED, channel-2, count);
		plane::flash(alarm, us, rightLED, channel-1, count);
		plane::beacons(alarm, markerLED, channel, count);
		//color_cycle::flash(alarm, rainbow[6-us], leds4, channel+1);
		count++;
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
		in_time = micros() - in_start;
	}
	
}
