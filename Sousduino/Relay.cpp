// 
// 
// 

#include "Relay.h"
#include "Pins.h"
#include "Arduino.h"

Relay::Relay(Pins p_pin) : pin(p_pin) {
	pinMode(pin, OUTPUT);

	off();
}

void Relay::on() {
	digitalWrite(pin, LOW);
}

void Relay::off() {
	digitalWrite(pin, HIGH);
}

bool Relay::is_on()
{
	return digitalRead(pin) == LOW ? true : false;
}
