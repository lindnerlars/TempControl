/**************************************************************************************************
 * AdafruitIO.ino
 *
 * Created: 07/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

// #define AIO_SERVER "io.adafruit.com"
// #define AIO_SERVERPORT 1883
#define AIO_USERNAME "lindnerlars"								// My Adafruit username (this can be changed on the webpage)
#define AIO_KEY "2667ac45f86940709ab399e234870689"				// My Adafruit IO Key (this can be changed on the webpage)
#define WIFI_SSID "INFINITUM7271_2.4"							// Wifi name
#define WIFI_PASS "MODEM08042020"								// Wifi Password


AdafruitIO_WiFi myIO(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *acttemp = myIO.feed("acttemp");
AdafruitIO_Feed *reftemp = myIO.feed("reftemp");
AdafruitIO_Feed *heateron = myIO.feed("heateron");

int actrefval = 0;
int oldrefval = 0;
bool refval_flag = false;


void setupAdafruitIO()
{
	Serial.println("Connecting to Adafruit IO");
	myIO.connect();
	reftemp->onMessage(handleMsgRefTemp);

	while(myIO.status() < AIO_CONNECTED)
	{
		Serial.print(".");
//		Serial.println(myIO.statusText());			// for debugging
		delay(500);
	}
	
	Serial.println();
	Serial.println(myIO.statusText());
	
	reftemp->get();
	
}


void runAdafruitIO()
{
	myIO.run();
}


void writeAdafruitIOTemp(float temper)
{
	acttemp->save(temper);
}


void writeAdafruitIOHeaterStatus()
{
	if (IsHeaterOn())
	{
		heateron->save(1);
	}
	else
	{
		heateron->save(0);		
	}
}


void handleMsgRefTemp(AdafruitIO_Data *data)
{
	actrefval = data->toInt();
	refval_flag = true;
}


int returnMsgRefTemp()
{
	return actrefval;
}


bool refval_changed()
{	
	return refval_flag;
}


void reset_refval()
{
	refval_flag = false;
}


