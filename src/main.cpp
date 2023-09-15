
#include "MyESP.hpp"
#include "ThingSpeak.h"

MyMotor MyESP::myMotor;
MyESP myESP;
void setup() {

	
int didPageStart = 0;
//		EEPROM.begin(512);
//		EEPROM.write(350, 12);
//	EEPROM.commit();
	myESP.startWiFi();

	//if (myESP.doesPushButtonPrest())
	if (1)
	{
		myESP.startPage();
			if(myESP.checkIfWatering())
			{
					myESP.watering();
			}
//		myESP.blinkFast();
//		didPageStart = 1;
	}
	else
	{
		if (myESP.checkIfWatering())
		{
			myESP.watering();
			myESP.saveWateringTime();
			myESP.saveDataToThinkSpeak();
			myESP.writeLastWateringH();
		} else
		{
			ESP.deepSleep(20*60e6);
		}
	} 
}

void loop() {
//	if( didPageStart )
//	{
//		myESP.handle();
//	}

}

