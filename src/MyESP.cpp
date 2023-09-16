#include "MyESP.hpp"
//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>

MyESP::MyESP()
{
Serial.begin(115200);	

  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(LED_BUILTIN, 1024);
  measuer5minuts.attach(300, goSleep);

 // h_water = EEPROM.read(1);
// act_line = EEPROM.read(299);
  delay(100);
  pinMode(pushButton,  INPUT_PULLUP  );
  pinMode(IPButton,  INPUT_PULLUP  );
  ticker.attach(0.6, tick);
  czas = "";
}


MyESP::~MyESP() {}

int MyESP::doesPushButtonPrest()
{
 return digitalRead(pushButton) == 0;
}

void MyESP::blinkFast()
{
	ticker.detach();
	ticker.attach(0.1, tick);
}

int MyESP::startWiFi()
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) { 
        delay(500);
  Serial.print(". ");
  }
  Serial.println(WiFi.localIP());
  czas = getDateAndTime();
  return 1;
}

String MyESP::getDateAndTime()
{
	WiFiClient wifiClient;

    const char *host = "http://worldtimeapi.org/api/timezone/Europe/Warsaw";
    HTTPClient http; 
    http.begin(wifiClient, host);
  int httpCode = http.GET();            //Send the request
  String payload;
//  while (httpCode != 200)
//  {
         payload = http.getString();    //Get the response payload from server
  //       nCon++;
         delay(100);
  //       if (nCon > 10)
  //       {
   //     ESP.deepSleep(60*60e6);
    //         return -1;
    //     }
 // }
  if(httpCode == 200)
  {
        const size_t capacity = JSON_OBJECT_SIZE(15) + 350;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, payload);
        String out = doc["datetime"]; // "2020-04-23T12:18:56.028849+02:00"
        return out;
  }
  
  String er = "-1";
  return er;
}

int MyESP::setStopWateringTime()
{
	ticker.detach();
	analogWrite(LED_BUILTIN, 0);
  EEPROM.begin(512);
  int time_water = EEPROM.read(0);
  Serial.println("Time_water: ");
  Serial.print(time_water);
	ticker.attach(2*time_water+10, motorStop);
	return 0;
}

void MyESP::watering()
{
	setStopWateringTime();
	startWatering();
}

void MyESP::startWatering(){
  EEPROM.begin(512);
  int time_water = EEPROM.read(0);
	myMotor.startWatering(time_water);
}

void MyESP::saveWateringTime()
{
  EEPROM.begin(512);
  for(int i = 0; i < 20; i++)
  {
    EEPROM.write(20*act_line + (i+2), czas[i]);
    //delay(10);
    EEPROM.commit();
  }
    act_line++;
    if (act_line > 9) act_line = 0;
  EEPROM.write(299, act_line);
      EEPROM.commit();
    
}

void MyESP::writeLastWateringH()
{

  EEPROM.begin(512);
    EEPROM.write(230, getH());
      EEPROM.commit();
}

int MyESP::readLastWateringH()
{
  EEPROM.begin(512);
   return EEPROM.read(230);
}

int MyESP::getH()
{
	int posTime = czas.indexOf("T");
 	return (czas[posTime + 1] - '0') * 10 + (czas[posTime+2] - '0');
}

int MyESP::checkIfWatering()
{
 EEPROM.begin(512);
 int n_line = EEPROM.read(380);
 int actual_h = getH();
 Serial.println("Actual_h - ");
 Serial.println(actual_h);
for (int i = 0; i < n_line; i++)
{
    int z = EEPROM.read(350 + i);
    if (z == actual_h and z != readLastWateringH()) 
	    return 1;
}
return 0;
}

void MyESP::startPage()
{

 page = load_page(); 
  server.on("/", HTTP_GET, [&](AsyncWebServerRequest *request){
    request->send(200, "text/html", "" + page + "");
  });
//const char *c = page.c_str();

//server.on("/", [&](AsyncWebServerRequest *request){
//	    request->send_P(200, "text/html", c);
//});
  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/act", HTTP_GET, [&] (AsyncWebServerRequest *request) {
		  EEPROM.begin(512);
    String inputMessage;
    String inputParam;
    String in;
    int dl_podlewania;
    int h_podlewania[24] {0};
    bool first_time = true;
    int n = 0;
    for (int i =  0; i < 24; i++)
    {
	String IN = "text";
	IN += i;
    if (request->hasParam(IN)) {
    		in = request->getParam(IN)->value();
    	int t1 = in.toInt();
		EEPROM.write(350+n, t1);
	EEPROM.commit();
	n++;
    	}
    }
    if(n)
    {
        EEPROM.write(380, n);
	EEPROM.commit();
    }
    if (request->hasParam("czas")) {
    	in = request->getParam("czas")->value();
	int t1 = in.toInt();
        EEPROM.write(0, t1);
	EEPROM.commit();
		
    }
 page =  load_page();
    request->send(200, "text/html", "" + page + "");
  });

 // server.onNotFound(notFound);
  server.begin();

}

void MyESP::handle()
{
//	server.handleClient();
}

void MyESP::saveDataToThinkSpeak()
{

	WiFiClient  client;
	ThingSpeak.begin(client);
	 #define SECRET_CH_ID1 1111943                                 // replace 0000000 with your channel number
	 #define SECRET_WRITE_APIKEY1 "G59OSUJY626RRWWJ"                           // replace XYZ with your channel write API Key
	unsigned long myChannelNumber = SECRET_CH_ID1;
	const char * myWriteAPIKey = SECRET_WRITE_APIKEY1;

  EEPROM.begin(512);
  int time_water = EEPROM.read(0);
	int httpCode = ThingSpeak.writeField(myChannelNumber, 1,time_water , myWriteAPIKey);

	 if (httpCode == 200) {
	      //Serial.println("Channel write successful.");
	 }
	 else {
	      // Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
	 }
	client.stop();
}


MyMotor::MyMotor(int STBY, int PWMA, int AIN1, int AIN2, int BIN1, int BIN2) 
	: STBY_(STBY), PWMA_(PWMA), AIN1_(AIN1), AIN2_(AIN2), BIN1_(BIN1), BIN2_(BIN2)
{
    pinMode(STBY_, OUTPUT);
    pinMode(PWMA_, OUTPUT);
    pinMode(AIN1_, OUTPUT);
    pinMode(AIN2_, OUTPUT);
    pinMode(BIN1_, OUTPUT);
    pinMode(BIN2_, OUTPUT);

    digitalWrite(AIN1_, LOW);
    digitalWrite(AIN2_, HIGH);
    digitalWrite(BIN1_, LOW);
    digitalWrite(BIN2_, HIGH);
    analogWrite(PWMA_, 1023);
    digitalWrite(STBY_, LOW);
}

void MyMotor::startWatering_A(int time_w)
{
    digitalWrite(STBY_, HIGH);

    digitalWrite(AIN1_, HIGH);
    digitalWrite(AIN2_, LOW);
    digitalWrite(BIN2_, HIGH);

    delay(time_w*1000);
}

void MyMotor::startWatering_B(int time_w)
{
    digitalWrite(STBY_, HIGH);

    digitalWrite(AIN1_, HIGH);
    digitalWrite(AIN2_, HIGH);
    digitalWrite(BIN2_, LOW);

    delay(time_w*1000);
}

void MyMotor::startWatering(int time_w)
{
	startWatering_A(time_w);
	startWatering_B(time_w);
}

void MyMotor::stopWatering()
{
    digitalWrite(STBY_, LOW); 
}
