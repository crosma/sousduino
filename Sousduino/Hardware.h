// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LED.h"
#include "Pins.h"
#include "Temperature.h"
#include "WiFiControl.h"
#include "Shit.h"

class Hardware
{
	Hardware();

protected:


public:
	static Hardware *getInstance()
	{
		static Hardware *instance;

		if (!instance) {
			shit("Initializing Hardware Singleton");

			instance = new Hardware();
		}

		return instance;
	}

	void blink_leds();

	LED *ap_led = new LED(Pins::AP_LED);
	LED *client_led = new LED(Pins::Client_LED);

	Temperature *temperature = new Temperature(Pins::OneWireBus);

};


#endif

