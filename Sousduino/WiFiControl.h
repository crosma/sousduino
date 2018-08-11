// WiFi.h

#ifndef _WIFI_CONTROL_h
#define _WIFI_CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include "LED.h"
#include "Shit.h"

class WiFiControl
{
	WiFiControl();
	bool init_ap();
	bool init_client();

	void client_connected();
	void client_disconnected();

	bool client_is_connecting = false;
	bool client_is_connected = false;

protected:


public:
	static WiFiControl *getInstance()
	{
		static WiFiControl *instance;

		if (!instance) {
			shit("Initializing WiFiControl Singleton");

			instance = new WiFiControl();
		}

		return instance;
	}

	friend void WiFiEvent(WiFiEvent_t event);

	void client_check_connection();
};


#endif

