/**************************************************************************************************
 * Heater.ino
 *
 * Created: 10/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

bool heateron_flag = false;


void setupHeater()
{
	pinMode(D7, OUTPUT);
}


void switchHeater(int refTemp)
{
	int actTemp = (int)readThermo();
		
	if (refTemp > actTemp)
	{
		heateron_flag = true;
		digitalWrite(D7, HIGH);
	}
	
	if (refTemp < actTemp)
	{
		heateron_flag = false;
		digitalWrite(D7, LOW);
	}
	
}


bool IsHeaterOn()
{
	return heateron_flag;
}
