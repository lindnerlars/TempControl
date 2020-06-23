/**************************************************************************************************
 * LCD.ino
 *
 * Created: 07/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

LiquidCrystal_I2C myLCD(0x27,2,1,0,4,5,6,7);					// 0x27 is I2C address, EN,RW ,RS ,D4,D5,D6,D7


void setupLCD()
{
	myLCD.begin(16,2);					// initializing the LCD 16 x 2
	myLCD.setBacklightPin(3,POSITIVE);	// Enable or Turn On the backlight
	myLCD.setBacklight(HIGH);
	
	myLCD.home();
	myLCD.print("Hello World");			// Start Print text to Line 1
	myLCD.setCursor(0, 1);
	myLCD.print("Start loop()....");		// Start Print Test to Line 2
}


void writeLCD(int potval, float temper)
{
	myLCD.home();
	myLCD.print("Soll: ");
	myLCD.print(potval);
	myLCD.print(" [C]");
	myLCD.setCursor(0, 1);
	myLCD.print("Ist : ");
	myLCD.print(temper);
	myLCD.print(" [C]");
	
}


void clearLCD()
{
	myLCD.clear();	
}
