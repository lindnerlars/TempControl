/* 
	Editor: https://www.visualmicro.com/
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the _vm sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: LOLIN(WEMOS) D1 R2 & mini, Platform=esp8266, Package=esp8266
*/

#define __ESP8266_ESp8266__
#define __ESP8266_ESP8266__
#define ARDUINO 108012
#define ARDUINO_MAIN
#define F_CPU 80000000L
#define printf iprintf
#define __ESP8266__
#define __ets__
#define ICACHE_FLASH
#define NONOSDK22x_190703 1
#define F_CPU 80000000L
#define LWIP_OPEN_SRC
#define TCP_MSS 536
#define LWIP_FEATURES 1
#define LWIP_IPV6 0
#define ARDUINO 108012
#define ARDUINO_ESP8266_WEMOS_D1MINI
#define ARDUINO_ARCH_ESP8266
#define FLASHMODE_DIO
#include "pins_arduino.h" 
#include "arduino.h"
#include "WemosD1_IOT.ino"
#include "AdafruitIO.ino"
#include "Heater.ino"
#include "LCD.ino"
#include "Poti.ino"
#include "Thermo.ino"
#include "Wifi.ino"
