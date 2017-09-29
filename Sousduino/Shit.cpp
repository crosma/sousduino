// 
// 
// 

#include "Shit.h"
#include "Arduino.h"

unsigned long last_millis_shit = millis();
void shit(const char *log, bool newline = true)
{
	unsigned long mil = millis();
	unsigned long diff = mil - last_millis_shit;
	last_millis_shit = mil;

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
