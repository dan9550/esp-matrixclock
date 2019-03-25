/*
 * ESP8266 driven matrix clock with weather
 * (c)2016-2018 Adam Kovesdi
 * version 3
 */

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Time.h>

#include "wifi.h"
#include "ntp.h"
#include "fonts.h"
#include "max7219.h"
#include "display.h"
#include "weather.h"

#include "settings.h"

// ntp stuff
NTP NTPclient;

// weather related stuff
time_t lastweatherinfoupdate=0;			// last weather update EPOCH timestamp

bool reset_trigger = false;

time_t getNTPtime(void)
{
  return NTPclient.getNtpTime();
}

void refresh_weather()
{
	if(now() > (lastweatherinfoupdate + WEATHER_POLL_INTERVAL))
	{
		lastweatherinfoupdate = now();
		// Serial.println(apitoken);
		// Serial.println(cityid);
		getWeatherData(apitoken, cityid);
	}
}

void display_weather()
{
	refresh_weather();
	clr();
	int t=getTemp();
	char buf[6];
	if (strcmp(units, "metric") == 0) {
		sprintf(buf,"%dC",t);
	} else {
		sprintf(buf,"%dF",t);
	}
	drawString(0,font,buf);
	drawChar(24,weather_icons,getWeatherIcon());
	drawChar(18,winddir_icons,getWinddir());
	for(int i=0;i<getWindspeed();i++) setPixel(16+i,7,true); // wind speed scale
	refreshAll();
}

void display_clock()
{
	draw_clock(hour(), minute(), second());
}

void setup()
{
	Serial.begin(serialBuadRate);
	Serial.println(); Serial.println("boot"); Serial.println();

	// set flash button to config resetter
	pinMode(CONFIGRESETBUTTON, INPUT_PULLUP);

	initMAX7219();
	drawStringClr(0,font," Conn...");

	// Set WiFi parameters explicitly: autoconnect, station mode 
	setupWiFi();

	ArduinoOTA.setHostname("matrixclock");
    ArduinoOTA.setPassword("matrixclockfirmware");
	ArduinoOTA.begin(); 

  NTPclient.begin(NTPServer, timeZone);
  setSyncInterval(SECS_PER_HOUR);
  setSyncProvider(getNTPtime);

	drawStringClr(0,font,"link up");
}

void loop()
{
	uint8_t	timeslice=now() % swapTimeout;
	if ((timeslice >4) && (timeslice <8))
	{
		display_weather();
	}
	else
	{
		display_clock();
	}

	if (digitalRead(CONFIGRESETBUTTON)==LOW) {
		if (reset_trigger == false) {
			reset_trigger = true;
			Serial.println("Config reset button pressed, taking action");
			// reset wifi and ESP
			resetWiFi(); 
		}
	}

	ArduinoOTA.handle();
}
