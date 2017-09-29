// 
// 
// 

#include "Hardware.h"

Hardware::Hardware()
{
}

void Hardware::blink_leds()
{
	led_ap->do_blink();
	led_client->do_blink();
}
