/**************************************************************************************************
 * WemosD1_IOT.ino
 *
 * Created: 10/06/2020
 * Author: Lars Lindner
 *
// #define D0		16
// #define D1		5
// #define D2		4
// #define D3		0
// #define D4		2
// #define D5		14
// #define D6		12
// #define D7		13
// #define D8		15
// #define RX		3
// #define TX		1
***************************************************************************************************/


#include <ESP8266WiFi.h>										// To use the ESP8266 Wifi chip on the Wemos D1
#include <Adafruit_MAX31865.h>									// To use the Thermocouple Amplifier MAX31856
#include <LiquidCrystal_I2C.h>									// To use the Crystal LCD with I2C interface
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <AdafruitIO_WiFi.h>

typedef enum State{Poti, AdafruitIO, Default};					// States of a State Machine

const long intervalLCD = 250;									// Interval to write to the LCD
const long intervalHeat = 1000;									// Interval to switch the Heater
const long intervalIO = 5000;									// Interval to write to Adafruit IO
unsigned long prevMillisPot = 0;
unsigned long prevMillisIO = 0;
unsigned long prevMillisHeat = 0;

State state = Default;
int temperHeater = 0;
int temperLCD = 0;


void setup()
{
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	
	setupHeater();	
	setupAdafruitIO();
	setupThermo();
 	setupLCD();
	
	// Signal for user that Wemos starts with the loop()
	for (int i = 0; i < 4; i++)
	{
		digitalWrite(LED_BUILTIN, LOW);			// LOW on the ESP8266 means ON
		delay(250);
		digitalWrite(LED_BUILTIN, HIGH);		// High on the ESP8266 means OFF
		delay(250);
	}
	
	clearLCD();
}


void loop() 
{
	// This function must be at the beginning of the main loop() according to Adafruit
	runAdafruitIO();
	
	unsigned long currMillis = millis();
	defState();

	// Only read Poti + Thermo and Print to LCD every intervalPot
	if (currMillis - prevMillisPot >= intervalLCD)
	{
		prevMillisPot = currMillis;

		if (state == Poti)
		{
			temperLCD = returnPotVal();
		} 
		else if (state == AdafruitIO)
		{
			temperLCD = returnMsgRefTemp();
		}		  
		writeLCD(temperLCD, readThermo());
	}

	// Only switch Heater every intervalHeat
	if (currMillis - prevMillisHeat >= intervalHeat)
	{
		prevMillisHeat = currMillis;
		
		if (state == Poti)
		{
			temperHeater = returnPotVal();
		}
		else if (state == AdafruitIO)
		{
			temperHeater = returnMsgRefTemp();
		}
		switchHeater(temperHeater);
	}

	// Only send data to Adafruit IO every intervalIO
	if (currMillis - prevMillisIO >= intervalIO)
	{
		prevMillisIO = currMillis;
		writeAdafruitIOTemp(readThermo());
		writeAdafruitIOHeaterStatus();
	}
	
 	// This yield() function is needed for the ESP8266 to liberate MCU time for Wifi Activity
	yield();
}


void defState()
{
	if (refval_changed())
	{
		state = AdafruitIO;
		reset_refval();
	}
	else if (potval_changed())
	{
		state = Poti;
	}
}