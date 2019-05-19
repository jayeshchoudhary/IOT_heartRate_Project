#include <ESP8266WiFi.h>

#include <WiFiClient.h>

#include <ThingSpeak.h>

const char* ssid = "Note 7"; //Your Network SSID

const char* password = "password@@"; //Your Network Password

int val;

int LDRpin = D0; //LDR Pin Connected at A0 Pin



WiFiClient client;

unsigned long myChannelNumber = 758696; //Your Channel Number (Without Brackets)

const char * myWriteAPIKey = "XWDQRWMI26JUMFA8"; //Your Write API Key

void setup()

{

Serial.begin(9600);

delay(10);

// Connect to WiFi network

WiFi.begin(ssid, password);



ThingSpeak.begin(client);

pinMode(LED_BUILTIN, OUTPUT);

}



void loop()

{

digitalWrite(LED_BUILTIN, LOW);


//val = analogRead(LDRpin); //Read Analog values and Store in val variable
val = random(66,75);
Serial.println(val); //Print on Serial Monitor

delay(1000);

ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey); //Update in ThingSpeak



delay(1000);
digitalWrite(LED_BUILTIN, HIGH);



}
