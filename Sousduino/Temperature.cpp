// 
// 
// 

#include "Temperature.h"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <string>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "Shit.h"

using namespace std;

Temperature::Temperature(Pins bus_id) {
	shit("Init Temperature");

	OneWire oneWire(bus_id);
	DS18B20 = DallasTemperature(&oneWire);

	DS18B20.begin();

	updateTemperature();
}

Temperature::~Temperature() {

}

float Temperature::updateTemperature() {
	float temp;

	//do {
		shit("Before requestTemperatures");

		DS18B20.requestTemperatures();

		shit("Before getTempFByIndex");

		temp = DS18B20.getTempCByIndex(0);

		//if (temp == 85.0 || temp == (-127.0)) delay(100);

	//} while (temp == 85.0 || temp == (-127.0));

	shit("Temperature for the device 1 (index 0) is: ", false);
	Serial.println(temp);

	lastTemperature = temp;

	shit("After temp");

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