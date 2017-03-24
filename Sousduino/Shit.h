// Shit.h

#ifndef _SHIT_h
#define _SHIT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


void shit(const char *log, bool newline);
void shit(const char *log);

#endif

