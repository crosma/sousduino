// Temperature.h

#ifndef _TEMPERATURE_h
#define _TEMPERATURE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include "Pins.h"

using namespace std;

class Temperature {
	DallasTemperature DS18B20;
	float lastTemperature = 0;

public:
	Temperature(Pins bus_id);
	~Temperature();
	float updateTemperature();
	float getLastTemperature();
	char* formatTemperature(float temperature);
	char* getTemperatureString();
};


#endif

