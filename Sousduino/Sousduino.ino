#include "Relay.h"
#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <string.h>
#include <Stream.h>
#include <Ticker.h>
#include <OneWire.h>
#include <RTClib.h>
#include <ArduinoJson.h>



#include "Pins.h"
#include "Shit.h"
#include "Temperature.h"
#include "LED.h"
#include "Config.h"
#include "WiFiControl.h"
#include "Hardware.h"


//JSON https://bblanchon.github.io/ArduinoJson/doc/
//Settings storage example Examples -> ESP8266 -> ConfigFile
//Checkout the wifi event handler to keep track of wifi connection

/* TODO:
When in AP mode, turn on red light.
When connected to WIFI turn on green light.
When trying WIFI client either blink green light or turn both on?

Store network info and reconnect at setup if possible.
When client fails, log it and show the user when they connect to AP
Allow the user to set a static IP? Prefill box with "192.168.1.121"
Turn off AP when station is connected? If so, provide a reset button.
*/

RTC_DS3231 rtc;

//Stuff
Config *config;
Hardware *hardware;
WiFiControl *wifiControl;

//Tickers
Ticker ticker_temperatures;
Ticker ticker_blink_leds;

void update_temperature() {
	//hardware->temperature->updateTemperature();
}

void blink_leds() {
	hardware->blink_leds();
}


unsigned long last_millis_sleep = millis();
unsigned long last_temp_check = 0;

void sleep(unsigned long duration)
{
	unsigned long mil_new = millis();
	long since = (long)mil_new - (long)last_millis_sleep;

	if (since < duration) {
		delay(duration - since);
	}

	last_millis_sleep = millis();
}

String getHeader()
{
	return
		"<!doctype html>\n"
		"<html>\n"
		"<head>\n"
		"	<title>Kombucha</title>\n"
		"	<style>body {font-size: 20px;}</style>\n"
		//"	<meta http-equiv=\"refresh\" content=\"10\" >";
		"</head>\n"
		"<body>\n\n"
		;
}

String getFooter()
{
	return
		"\n\n</body>\n"
		"</html>\n"
		;
}

String getRoot()
{
	String html = getHeader();

	html += "Cabinet Temperature: <b>";
	html += hardware->temperature->getLastTemperature();
	html += "F</b><br>";

	html += "Relay: <b>";
	html += hardware->relay1->is_on() ? "On" : "Off";
	html += "</b><br>";

	html += "<br>";
	html += "<br>";
	html += "IP Address: ";
	html += WiFi.localIP().toString();

	html += "<br>";
	html += "<br>";
	html += "<input type=\"button\" value=\"Refresh Page\" onClick=\"window.location.reload()\">";

	

	html += getFooter();

	return html;
}

void handleRoot()
{
	shit("Serving Root");

	hardware->server.send(200, "text/html", getRoot());
}

//https://github.com/bblanchon/ArduinoJson
void handleJSON()
{
	StaticJsonBuffer<200> jsonBuffer;

	JsonObject& root = jsonBuffer.createObject();
	root["temperature"] = hardware->temperature->getLastTemperature();
	root["relay"] = hardware->relay1->is_on();

	String output;
	root.printTo(output);

	shit(output.c_str());

	hardware->server.send(200, "text/json", output);
}

void handleNotFound()
{
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += hardware->server.uri();
	message += "\nMethod: ";
	message += (hardware->server.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += hardware->server.args();
	message += "\n";

	for (uint8_t i = 0; i<hardware->server.args(); i++) {
		message += " " + hardware->server.argName(i) + ": " + hardware->server.arg(i) + "\n";
	}

	hardware->server.send(404, "text/plain", message);
}


void setupWebServer()
{
	hardware->server = ESP8266WebServer(80);

	hardware->server.on("/", handleRoot);
	hardware->server.on("/json", handleJSON);

	hardware->server.onNotFound(handleNotFound);

	hardware->server.begin();

	shit("HTTP server set up");
}

void setup()
{
	//Start the Serial Port
	delay(1000);
	Serial.begin(115200);
	shit("Starting up");

	config = Config::getInstance();
	hardware = Hardware::getInstance();
	wifiControl = WiFiControl::getInstance();

	//Start the tickers
	//ticker_temperatures.attach(1, update_temperature);
	ticker_blink_leds.attach(0.75, blink_leds); 

	setupWebServer();

	hardware->led_boot->on();
}


void loop()
{
	if (millis() - last_temp_check > 3000) {
		hardware->temperature->updateTemperature();
		float temp = hardware->temperature->getLastTemperature();

		if (temp > config->goal_temp + config->threshold) {
			hardware->relay1->off();
			hardware->led_relay1->off();
		}
		else if (temp < config->goal_temp - config->threshold) {
			hardware->relay1->on();
			hardware->led_relay1->on();
		}

		shit("Current temperature: ", false);
		Serial.print(temp);
		Serial.println(hardware->relay1->is_on() ? " (ON)" : " (OFF)");

		last_temp_check = millis();
	}

	hardware->server.handleClient();
}