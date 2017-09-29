// Relay.h

#ifndef _RELAY_h
#define _RELAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Pins.h"

class Relay {
private:
	Pins pin;

public:
	Relay(Pins pin);
	void on();
	void off();
	bool is_on();
};


#endif

