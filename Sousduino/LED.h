// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Pins.h"

class LED {
  private:
    Pins pin;
    bool is_on;
    bool is_blinking;
    void _on();
    void _off();

  public:
    LED(Pins pin);
    void on();
    void off();
    void blink();
    void do_blink();
};

#endif

