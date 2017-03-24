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

	Relay1 = 10,
	Relay2 = 11,

	AP_LED = 4,
	Client_LED = 5,
	Built_In_LED = 16,
};

#endif

