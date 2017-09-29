// Hardware.h

#ifndef _HARDWARE_h
#define _HARDWARE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LED.h"
#include "Relay.h";
#include "Pins.h"
#include "Temperature.h"
#include "WiFiControl.h"
#include "Shit.h"
#include <ESP8266WebServer.h>

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

	LED *led_ap = new LED(Pins::LED_AP);
	LED *led_client = new LED(Pins::LED_Client);
	LED *led_boot = new LED(Pins::LED_Boot);
	LED *led_relay1 = new LED(Pins::LED_Relay1);

	Temperature *temperature = new Temperature(Pins::OneWireBus);

	Relay *relay1 = new Relay(Pins::Relay1);
	Relay *relay2 = new Relay(Pins::Relay2);

	ESP8266WebServer server;
};


#endif

