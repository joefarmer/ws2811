//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef COLOR_CYCLE_HPP_
#define COLOR_CYCLE_HPP_
#include "ws2811_8.h"

namespace color_cycle
{

template< uint8_t size>
void scroll( ws2811::rgb new_value, ws2811::rgb (&range)[size])
{
    for (uint8_t idx = size-1; idx != 0 ; --idx)
    {
        range[idx] = range[idx -1];
    }
    range[0] = new_value;
}

template< uint8_t led_count>
void animate( const ws2811::rgb &new_value, ws2811::rgb (&leds)[led_count], uint8_t channel)
{
    scroll( new_value, leds);
    send( leds, channel);
    _delay_ms(55);
}

template<uint8_t count, uint8_t led_count>
void color_cycle( ws2811::rgb (&sequence)[count], ws2811::rgb (&leds)[led_count], uint8_t channel)
{
	for (;;)
	{
		for (uint8_t idx = 0; idx != count; ++idx)
		{
			animate( sequence[idx], leds, channel);
		}
		for (uint8_t idx = count; idx != 0; --idx)
		{
			animate( sequence[idx-1], leds, channel);
		}

	}
}

void example_color_cycle( uint8_t channel)
{
	using ws2811::rgb;
	rgb leds[6];
	
	rgb sequence[] = {
			rgb( 0, 255, 0),
			rgb( 0, 0, 0),
			rgb( 0, 255, 0),
			rgb( 0, 0, 0),			
			rgb( 0, 255, 0),
			rgb( 0, 0, 0),			
			rgb( 0, 0, 0),			
			rgb( 0, 0, 0),			
			rgb( 0, 0, 0),			
			rgb( 255, 0, 0),
			rgb( 0, 0, 0),			
			rgb( 255, 0, 0),
			rgb( 0, 0, 0),			
			rgb( 255, 0, 0),
			rgb( 0, 0, 0)			
	};
/*
	rgb sequence[] = { rgb( 0, 0, 0) };
	const int step = 16; // Select this to be a power of two if you want the maximum brightness to be reachable

	for(;;){
		for( int red = 0x00; red <= 0xFF; red += step ) {
			for( int green = 0x00; green <= 0xFF; green += step ) {
				for( int blue = 0x00; blue <= 0xFF; blue += step ) {
					sequence = { rgb(red, green, blue) };
					send(sequence, channel);
					_delay_ms(33);
				}
			}
		}
	}	
	
	
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

	rgb sequence[] = {
		rgb( 255, 0, 0),
		rgb( 0, 0, 0),			
		rgb( 255, 0, 0),
		rgb( 0, 0, 0),			
		rgb( 255, 0, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 192, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 192, 0),
		rgb( 0, 0, 0),	
		rgb( 255, 192, 0),
		rgb( 0, 0, 0),	
		rgb( 0, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 0, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 0, 127, 0),
		rgb( 0, 0, 0),	
		rgb( 0, 0, 255),
		rgb( 0, 0, 0),	
		rgb( 0, 0, 255),
		rgb( 0, 0, 0),	
		rgb( 0, 0, 255),
		rgb( 0, 0, 0),	
		rgb( 127, 0, 127),
		rgb( 0, 0, 0),	
		rgb( 127, 0, 127),
		rgb( 0, 0, 0),	
		rgb( 127, 0, 127),
		rgb( 0, 0, 0)		
	};

	*/


	color_cycle( sequence, leds, channel);

}
}

#endif /* COLOR_CYCLE_HPP_ */
