// 
// 
// 

#include "Hardware.h"

Hardware::Hardware()
{
}

void Hardware::blink_leds()
{
	ap_led->do_blink();
	client_led->do_blink();
}
