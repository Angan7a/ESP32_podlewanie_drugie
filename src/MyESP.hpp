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
#include <HTTPClient.h>

#define EEPROM_SIZE 512
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  58        /* Time ESP32 will go to sleep (in seconds) */

class MyMotor {
	int PWMA_ = 32; //Speed control
	int AIN2_ = 33; //Direction
	int AIN1_ = 25; //Direction
	int STBY_ = 26; //standby
	int BIN1_ = 27; //Direction 1
	int BIN2_ = 14; //Direction 0
	int PWMB_ = 12; //Speed control
	//Motor A
	int time_wait = 0;
	Ticker d;
	static void wait()
	{
		static int time_elaps = 0;
		time_elaps++;
	}
public:
	MyMotor(int STBY = 26, int PWMA = 32, int PWMB = 12, int AIN1 = 25, int AIN2 = 33, int BIN1 = 27, int BIN2 = 14);

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
const char* ssid = "CGA2121_VzpmSRV";
const char* password = "b1e514f452ea181e991056b9cbee3df73acdb2c5e8bc6dafcd96c66a9840bb48";
//	const char* ssid="FunBox2-F968";
//	const char* password ="CD3EE7CC7CC7967A39EEFD1721";
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
public:
	static void goSleep()
	{
	  // ESP.deepSleep(20*60e6);
	    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
    Serial.println("Going to sleep now");
  Serial.flush();
  esp_deep_sleep_start();
	}
    String getDateAndTime();
public:
	String myIP;
    void blinkFast();
    static MyMotor myMotor;
    //virtual int readEEPROM(int);
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


