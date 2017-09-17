// 
// 
// 

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include "WiFiControl.h"
#include "Shit.h"
#include "Config.h"
#include "Hardware.h"

void WiFiEvent(WiFiEvent_t event) {
	WiFiControl *wifiControl = WiFiControl::getInstance();

	switch (event) {
	case WIFI_EVENT_STAMODE_GOT_IP:
		wifiControl->client_connected();
		break;

	case WIFI_EVENT_STAMODE_DISCONNECTED:
		wifiControl->client_disconnected();
		break;

	default:
		//Serial.printf("[Unhandled WiFi-event] event: %d\n", event);
		break;
	}
}

void WiFiOnConnected(WiFiEventStationModeConnected info)
{

}

void WiFiOnDisonnected(WiFiEventStationModeDisconnected info)
{
	
}

void WiFiStationModeAuthModeChanged(WiFiEventStationModeAuthModeChanged info)
{

}

void WiFiStationModeGotIP(WiFiEventStationModeGotIP info)
{

}

void WiFiStationModeDHCPTimeout(void)
{

}

void WiFiSoftAPModeStationConnected(WiFiEventSoftAPModeStationConnected info)
{
	shit("WiFiSoftAPModeStationConnected");
	//shit(info.mac);
}

void WiFiSoftAPModeStationDisconnected(WiFiEventSoftAPModeStationDisconnected info)
{

}


WiFiControl::WiFiControl() {
	init_ap();
	init_client();
}

bool WiFiControl::init_ap()
{
	Config *config = Config::getInstance();
	Hardware *hardware = Hardware::getInstance();

	WiFi.softAPdisconnect(false); //kill old AP settings just in case

	shit("Starting WiFi AP...");

	hardware->ap_led->off();

	WiFi.onSoftAPModeStationConnected(WiFiSoftAPModeStationConnected);
	WiFi.onSoftAPModeStationDisconnected(WiFiSoftAPModeStationDisconnected);
	
	WiFi.mode(WIFI_AP_STA); //Turn on AP+Station mode
	WiFi.hostname(config->ap_ssid);
	WiFi.softAPConfig(config->ap_gateway, config->ap_gateway, config->ap_netmask);
	WiFi.softAP(config->ap_ssid, config->ap_password);

	shit("WiFi AP Ready @ ", false);
	Serial.println(WiFi.softAPIP());


	hardware->ap_led->on();

	return true;
}

bool WiFiControl::init_client()
{
	Config *config = Config::getInstance();
	Hardware *hardware = Hardware::getInstance();

	WiFi.disconnect(true); //make sure the old config is gone

	shit("Starting WiFi Client...");

	hardware->client_led->blink();
	
	WiFi.onEvent(WiFiEvent);
	WiFi.onStationModeConnected(WiFiOnConnected);
	WiFi.onStationModeDisconnected(WiFiOnDisonnected);
	WiFi.onStationModeAuthModeChanged(WiFiStationModeAuthModeChanged);
	WiFi.onStationModeGotIP(WiFiStationModeGotIP);
	//WiFi.onStationModeDHCPTimeout(WiFiStationModeDHCPTimeout);

	WiFi.begin("WhiteHorse", "5095826948"); //TODO: Needs to be in config
}

void WiFiControl::client_connected()
{
	Hardware *hardware = Hardware::getInstance();

	shit("WiFi connected @ ", false);
	Serial.println(WiFi.localIP());

	hardware->client_led->on();
}

void WiFiControl::client_disconnected()
{
	Hardware *hardware = Hardware::getInstance();

	shit("WiFi lost connection");

	hardware->client_led->off();
}

