//
// Copyright (c) 2013 Danny Havenith
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef PLANE_HPP_
#define PLANE_HPP_
#include "ws2811_8.h"

namespace plane
{
	uint8_t my_rand()
	{
		static uint16_t state;
		state += 33203;
		return static_cast<uint8_t>(state); // adding a prime number
	}
	
	template< uint8_t size>
	void scroll( ws2811::rgb new_value, ws2811::rgb (&range)[size])
	{
		// size-2 means don't trim off the indicator light
		for (uint8_t idx = size-2; idx != 0 ; --idx)
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
		_delay_ms(4);
	}
	
	template<uint8_t led_count>
	void flash(bool alarm, uint8_t us, ws2811::rgb (&leds)[led_count], uint8_t channel, uint8_t count)
	{
		//ws2811::rgb color; 

		if(alarm)
		{
			ws2811::rgb strobe = ws2811::rgb( 255, 0, 0);
			animate(strobe, leds, channel);
		}
		else
		{
			for (uint8_t idx = 0; idx != led_count; ++idx)
			{   
				animate(ws2811::rgb( my_rand(), my_rand(), my_rand()), leds, channel);		
			}
			
			for (uint8_t idx = led_count; idx != 0; --idx)
			{
				animate(ws2811::rgb( my_rand(), my_rand(), my_rand()), leds, channel);		
			}
		}
	}
	
	template<uint8_t led_count>
	void beacons(bool alarm, ws2811::rgb (&leds)[led_count], uint8_t channel, uint8_t count)
	{
		uint8_t on = 0;
		if(count % 2 == 0) 
		{
			on = 255;
		}
		
		leds[0] = ws2811::rgb(on, 0, 0);
		leds[1] = ws2811::rgb(on, 0, 0);
		leds[2] = ws2811::rgb(on, 0, 0);
		leds[3] = ws2811::rgb(on, 0, 0);
		leds[4] = ws2811::rgb(on, on, on);
		leds[5] = ws2811::rgb(on, on, on);		
	}
}

#endif 
