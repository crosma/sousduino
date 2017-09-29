// 
// 
// 

#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
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
	shit("WIFI CONNECTED");
}

void WiFiOnDisonnected(WiFiEventStationModeDisconnected info)
{
	shit("WIFI DISCONNECTED");
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
	//Serial.setDebugOutput(true);

	if (true) {
		WiFi.mode(WIFI_AP_STA); //Turn on AP+Station mode

		init_ap();
		init_client();
	}
	else {
		WiFi.mode(WIFI_AP);

		init_ap();
	}
}

bool WiFiControl::init_ap()
{
	Config *config = Config::getInstance();
	Hardware *hardware = Hardware::getInstance();

	WiFi.softAPdisconnect(false); //kill old AP settings just in case

	shit("Starting WiFi AP...");

	hardware->led_ap->off();

	WiFi.onSoftAPModeStationConnected(WiFiSoftAPModeStationConnected);
	WiFi.onSoftAPModeStationDisconnected(WiFiSoftAPModeStationDisconnected);

	WiFi.hostname(config->ap_ssid);
	WiFi.softAPConfig(config->ap_gateway, config->ap_gateway, config->ap_netmask);
	WiFi.softAP(config->ap_ssid, config->ap_password);

	shit("WiFi AP Ready @ ", false);
	Serial.println(WiFi.softAPIP());

	hardware->led_ap->on();

	return true;
}

bool WiFiControl::init_client()
{
	Config *config = Config::getInstance();
	Hardware *hardware = Hardware::getInstance();

	client_is_connected = false;

	WiFi.disconnect(true); //make sure the old config is gone

	shit("Starting WiFi Client...");

	hardware->led_client->blink();
	
	WiFi.onEvent(WiFiEvent);
	WiFi.onStationModeConnected(WiFiOnConnected);
	WiFi.onStationModeDisconnected(WiFiOnDisonnected);
	WiFi.onStationModeAuthModeChanged(WiFiStationModeAuthModeChanged);
	WiFi.onStationModeGotIP(WiFiStationModeGotIP);
	//WiFi.onStationModeDHCPTimeout(WiFiStationModeDHCPTimeout);

	IPAddress gateway(192, 168, 1, 1);
	IPAddress subnet(255, 255, 255, 0);

	WiFi.config(config->ip_address, gateway, subnet);
	WiFi.begin("WhiteHorse", "5095826948"); //Yes, I know this is my wifi password. Whatever. Come get some wifi?
}

void WiFiControl::client_connected()
{
	Config *config = Config::getInstance();
	Hardware *hardware = Hardware::getInstance();

	shit("WiFi connected @ http://", false);
	Serial.println(WiFi.localIP());

	hardware->led_client->on();

	client_is_connected = true;

	hardware->server.stop();
	hardware->server.begin();
	shit("HTTP server started");

	if (MDNS.begin(config->mDNSName)) {
		shit("MDNS responder started");
	}
	else {
		shit("MDNS responder failed to start");
	}
}

void WiFiControl::client_disconnected()
{
	if (!client_is_connected) return;

	Hardware *hardware = Hardware::getInstance();

	shit("WiFi lost connection");

	hardware->led_client->off();

	this->init_client();
}

