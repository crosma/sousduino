// 
// 
// 

#include "Shit.h"
#include "Arduino.h"

unsigned long last_millis = millis();
void shit(const char *log, bool newline = true)
{
	unsigned long mil = millis();
	unsigned long diff = mil - last_millis;
	last_millis = mil;

	Serial.print("[+");
	Serial.print(diff);
	Serial.print("] ");
	if (newline) {
		Serial.println(log);
	}
	else {
		Serial.print(log);
	}
}

void shit(const char *log) {
	shit(log, true);
}
