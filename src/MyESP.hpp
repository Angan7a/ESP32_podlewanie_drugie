#pragma once 
#include "Arduino.h"

//#include <ESP8266WiFi.h>
  #include <WiFi.h>
  #include <AsyncTCP.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
#include <ESPAsyncWebServer.h>
#include <time.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Ticker.h>
#include <DNSServer.h>
//#include <WiFiManager.h>
//#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "ThingSpeak.h"
#include "http.hpp"

#define EEPROM_SIZE 512
class MyMotor {
	int STBY_ = 12; //standby
	//Motor A
	int PWMA_ = 5; //Speed control
	int AIN1_ = 14; //Direction
	int AIN2_ = 4; //Direction
	int BIN1_ = 14; //Direction 1
	int BIN2_ = 1; //Direction 0
	int time_wait = 0;
	Ticker d;
	static void wait()
	{
		static int time_elaps = 0;
		time_elaps++;
	}
public:
	MyMotor(int STBY = 12, int PWMA = 5, int AIN1 = 14, int AIN2 = 4, int BIN1 = 14, int BIN2 = 1);

	void startWatering(int time_w);
	void startWatering_A(int time_w);
	void startWatering_B(int time_w);
	void stopWatering();
};

class MyESP {
protected:
	char akt_czas[10];
	int time_water;
	int h_water;
	String page = "";
	String pageIP = "";
	//int ledPin = 2; // onboard LED
	int pushButton = 13; // push button
	int IPButton = 14; // button to show IP
	int act_line;
//const char* ssid = "CGA2121_VzpmSRV";
//const char* password = "b1e514f452ea181e991056b9cbee3df73acdb2c5e8bc6dafcd96c66a9840bb48";
	const char* ssid="FunBox2-F968";
	const char* password ="CD3EE7CC7CC7967A39EEFD1721";
//const char* ssid = "TFO-WiFi";//type your ssid
//const char* password = "accessok";//type your password
	AsyncWebServer server{80};
	Ticker measuer5minuts;
	Ticker ticker;
	String czas;
        //WiFiManager wifiManager;
	static void motorStop()
	{
		analogWrite(LED_BUILTIN, 1024);
		myMotor.stopWatering();
        	//ESP.deepSleep(60*60e6);
		goSleep();
	}
	static void tick()
	{
		static int state = 1;
	  if (state)
	  {
		  analogWrite(LED_BUILTIN, 230);
	  } else
	  {
		  analogWrite(LED_BUILTIN, 1024);
	  }
	  state = !state;

	}
	static void goSleep()
	{
	   ESP.deepSleep(20*60e6);
	}
    String getDateAndTime();
public:
    void blinkFast();
    static MyMotor myMotor;
    virtual int readEEPROM(int);
    int getH();
    int doesPushButtonPrest();
    virtual int startWiFi();
    MyESP();
    int returnZero();
    void watering();
    virtual int setStopWateringTime();
    void startWatering();
    void saveWateringTime();
    int checkIfWatering();
    void startPage();
    void handle();
void saveDataToThinkSpeak();
void saveTempToThinkSpeak(float temp);
void writeLastWateringH();
int readLastWateringH();
    virtual ~MyESP();
};


