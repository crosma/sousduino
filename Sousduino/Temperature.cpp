// 
// 
// 

#include "Temperature.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <iomanip> // setprecision
#include <sstream> // stringstream

using namespace std;

Temperature::Temperature(Pins bus_id) {
	OneWire *oneWire = new OneWire(bus_id);
	DS18B20 = DallasTemperature(oneWire);

	updateTemperature();
}

Temperature::~Temperature() {

}

float Temperature::updateTemperature() {
	float temp;

	do {
		DS18B20.requestTemperatures();
		temp = DS18B20.getTempFByIndex(0);
		if (temp == 85.0 || temp == (-127.0)) delay(100);
	} while (temp == 85.0 || temp == (-127.0));

	lastTemperature = temp;

	return temp;
}

float Temperature::getLastTemperature()
{
	return lastTemperature;
}

char* Temperature::formatTemperature(float temperature)
{
	const int length = 3;
	const int precision = 2;

	char t[length + precision + 1];
	dtostrf(temperature, length, precision, t);

	return t;
}

char* Temperature::getTemperatureString() {
	return formatTemperature(this->updateTemperature());

}