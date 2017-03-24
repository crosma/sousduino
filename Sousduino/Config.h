// Config.h

#ifndef _CONFIG_h
#define _CONFIG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WiFiClient.h>
#include "Shit.h"

class Config
{
private:
	Config();


protected:


public:
	static Config *getInstance()
	{
		static Config *instance;

		if (!instance) {
			shit("Initializing Config Singleton");

			instance = new Config();
		}

		return instance;
	}

	void Save();


	char *ap_ssid = "Sousduino";
	char *ap_password = "password";
	IPAddress ap_gateway = IPAddress(192, 168, 1, 1);
	IPAddress ap_netmask = IPAddress(255, 255, 255, 0);
};


#endif

