#include <Arduino.h>
#include <ssd1309.h>
#include <ssd1322.h>
#include <ssd1327.h>

SSD1309 ssd1309;
SSD1322 ssd1322;
SSD1327 ssd1327;

void setup()
{
	Serial.begin(115200);
	Serial.println("");

	DisplayDriver::initAll();
	ssd1309.init();
	ssd1322.init();
	ssd1327.init();
}

void loop()
{
}
