/**************************************************************************************************
 * Thermo.ino
 *
 * Created: 07/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

#define RREF      430.0											// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RNOMINAL  100.0											// The 'nominal' 0-degrees-C resistance of the sensor. Use 100.0 for PT100, 1000.0 for PT1000


Adafruit_MAX31865 myThermo = Adafruit_MAX31865(D3, D4, D5, D6);	// Use software SPI: CS, SDI, SDO, CLK


void setupThermo()
{
	myThermo.begin(MAX31865_3WIRE);		// Start the MAX31865 to read the PT100 temperature sensor using a 3WIRE connection
	
}

float readThermo()
{
	uint16_t rtd = myThermo.readRTD();
	float temper_float = myThermo.temperature(RNOMINAL, RREF);

	//	// For debugging
	//   Serial.print("RTD value: "); Serial.println(rtd);
	//   float ratio = rtd;
	//   ratio /= 32768;
	//   Serial.print("Ratio = "); Serial.println(ratio,8);
	//   Serial.print("Resistance = "); Serial.println(RREF*ratio,8);
	//   Serial.print("Temperature = "); Serial.println(myThermo.temperature(RNOMINAL, RREF));

	// Check and print any faults via Serial
	uint8_t fault = myThermo.readFault();
	if (fault)
	{
		Serial.print("Fault 0x"); Serial.println(fault, HEX);
		if (fault & MAX31865_FAULT_HIGHTHRESH)
		{
			Serial.println("RTD High Threshold");
		}
		if (fault & MAX31865_FAULT_LOWTHRESH)
		{
			Serial.println("RTD Low Threshold");
		}
		if (fault & MAX31865_FAULT_REFINLOW)
		{
			Serial.println("REFIN- > 0.85 x Bias");
		}
		if (fault & MAX31865_FAULT_REFINHIGH)
		{
			Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
		}
		if (fault & MAX31865_FAULT_RTDINLOW)
		{
			Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
		}
		if (fault & MAX31865_FAULT_OVUV)
		{
			Serial.println("Under/Over voltage");
		}
		myThermo.clearFault();
	}
	
	return temper_float;
}


