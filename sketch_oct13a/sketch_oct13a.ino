#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#define switchs 12
#define light 13
char ssid[]="Binatone";
char pass[]="GrewalFamily999";
int sws;
int status=WL_IDLE_STATUS;
char host[]="https://7676hssfl5.execute-api.us-east-2.amazonaws.com";
char resource[]="/beta/arduino-id";
String postData;
String postVariable="id:";
WiFiClient client;
unsigned long time=0;
int prev;
long debug=200;
unsigned long prevtime;
unsigned long a=0;
String id="4545454uno:1";
void setup()
{
Serial.begin(9600);
pinMode(switchs,INPUT);
pinMode(light,OUTPUT);
while(status!=WL_CONNECTED)
{
  Serial.print("Attempting to connect to Network named:");
  Serial.println(ssid);
  status=WiFi.begin(ssid,pass);
  delay(1000);
  }
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip= WiFi.localIP();
  IPAddress gateway=WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}
void loop()
{
  sws=digitalRead(switchs);
    if(sws==HIGH){digitalWrite(light,HIGH);}
    else{digitalWrite(light,LOW);}
    if(sws==LOW && prev!=sws )
    {
        digitalWrite(light,HIGH);
        //Serial.print(id+",on");
        //Serial.print(",");
        a=time-prevtime;
        float sa=a/1000000;
        //Serial.print(a);
        //Serial.println();
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["id"]=id;
        root["status"]="on";
        root["time in seconds"]=sa;
        if(WiFi.status()==WL_CONNECTED)
        {
          root.printTo(Serial);
          HTTPClient http;
          http.begin(host);
          http.addHeader("Content-Type" ,"application/json");
          int httpCode=http.Post(resource);
          String payload=http.getString();
          Serial.println(httpCode);
          Serial.println("payload");
        prevtime=micros();
    }
   else if(sws==HIGH && prev!=sws)
   {
    prevtime=micros();
    }
    
    
    prev=sws;
    time=micros();
    delay(50);
     
}
