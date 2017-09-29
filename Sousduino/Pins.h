// Pins.h

#ifndef _PINS_h
#define _PINS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum Pins
{
	OneWireBus = D4,

	Relay1 = 5,
	Relay2 = 4,

	LED_Boot = 14,
	LED_Client = 12,
	LED_Relay1 = 13,

	LED_AP = 16,
	LED_Built_In = 16,
};

#endif

