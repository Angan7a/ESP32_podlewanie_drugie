
#include "MyESP.hpp"
#include "ThingSpeak.h"

MyMotor MyESP::myMotor;
MyESP myESP;
void setup() {

	
int didPageStart = 0;
	myESP.startWiFi();

	//if (myESP.doesPushButtonPrest())
	if (0)
	{
		myESP.startPage();
	}
	else
	{
		myESP.startPage();
		if (myESP.checkIfWatering())
		{
			myESP.watering();
			myESP.saveWateringTime();
			myESP.saveDataToThinkSpeak();
			myESP.writeLastWateringH();
		} else
		{
		//	ESP.deepSleep(20*60e6);
		}
	} 
}

void loop() {
}

