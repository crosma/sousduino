#include "Hardware.h"#include <ESP8266WebServer.h>#include <string.h>#include <Stream.h>#include <Ticker.h>#include <OneWire.h>#include "Pins.h"#include "Shit.h"#include "Temperature.h"#include "LED.h"#include "Config.h"#include "WiFiControl.h"#include "Arduino.h"#include <Arduino.h>//TRY new one wire library, its in examples -- it might be faster//JSON https://bblanchon.github.io/ArduinoJson/doc///Settings storage example Examples -> ESP8266 -> ConfigFile//Checkout the wifi event handler to keep track of wifi connection/* TODO:When in AP mode, turn on red light.When connected to WIFI turn on green light.When trying WIFI client either blink green light or turn both on?Store network info and reconnect at setup if possible.When client fails, log it and show the user when they connect to APAllow the user to set a static IP? Prefill box with "192.168.1.121"Turn off AP when station is connected? If so, provide a reset button.*/ESP8266WebServer server(80);//StuffConfig *config;Hardware *hardware;WiFiControl *wifiControl;//TickersTicker ticker_temperatures;Ticker ticker_blink_leds;void update_temperature() {	//hardware->temperature->updateTemperature();}void blink_leds() {	hardware->blink_leds();}void setup(){	delay(1000);	//Start the Serial Port	Serial.begin(115200);	shit("Starting up");	config = Config::getInstance();	hardware = Hardware::getInstance();	wifiControl = WiFiControl::getInstance();	//Start the tickers	ticker_temperatures.attach(1, update_temperature);	ticker_blink_leds.attach(0.75, blink_leds);}void loop(){	//shit("Loop");	//shit(hardware->temperature->getTemperatureString());	delay(10);}/*void init_web_server() {	MDNS.begin(ap_ssid);	server.on("/", handleRoot);	server.on("/inline", []() {		server.send(200, "text/plain", "this works as well");	});	httpUpdater.setup(&server);	server.onNotFound(handleNotFound);	server.begin();	MDNS.addService("http", "tcp", 80);	Serial.printf("HTTPUpdateServer ready! Open http://%s.local/update in your browser\n", ap_ssid);}void handleRoot() {	server.send(200, "text/html",		"<!doctype html>\<html>\<head>\  <meta charset=utf-8>\  <title>Sousduino</title>\  <base href=/>\  <meta name=viewport content=width=device-width, initial-scale=1>\  <link rel=icon type=image/x-icon href=favicon.ico>\</head>\<body>\  <app-root>Loading...</app-root>\  <script type=text/javascript src=http://localhost:4200/inline.bundle.js></script>\  <script type=text/javascript src=http://localhost:4200/polyfills.bundle.js></script>\  <script type=text/javascript src=http://localhost:4200/styles.bundle.js></script>\  <script type=text/javascript src=http://localhost:4200/vendor.bundle.js></script>\  <script type=text/javascript src=http://localhost:4200/main.bundle.js></script>\</body></html>");}void handleNotFound() {	String message = "File Not Found\n\n";	message += "URI: ";	message += server.uri();	message += "\nMethod: ";	message += (server.method() == HTTP_GET) ? "GET" : "POST";	message += "\nArguments: ";	message += server.args();	message += "\n";	for (uint8_t i = 0; i < server.args(); i++) {		message += " " + server.argName(i) + ": " + server.arg(i) + "\n";	}	server.send(404, "text/plain", message);}*/