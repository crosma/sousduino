// 
// 
// 

#include "LED.h"
#include "Pins.h"
#include "Arduino.h"
#include "Shit.h"

LED::LED(Pins p_pin) : pin(p_pin) 
{
	pinMode(pin, OUTPUT);

	off();
}

void LED::_on() 
{
	digitalWrite(pin, HIGH);
	is_on = true;
}

void LED::on() 
{
	_on();
	is_blinking = false;
}

void LED::_off() 
{
	digitalWrite(pin, LOW);
	is_on = false;
}

void LED::off() 
{
	_off();
	is_blinking = false;
}

void LED::blink()
{
	_on();
	is_blinking = true;
}

void LED::do_blink() 
{
	if (is_blinking) {
		if (is_on) {
			_off();
		}
		else {
			_on();
		}
	}
}