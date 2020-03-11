#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
#include<ArduinoJson.h>
#define switchs D7
#define light D0

#define ssid[]="Binatone"
#define pass[]="Grewalfamily999"
int sws;

char host[]="https://7676hssfl5.execute-api.us-east-2.amazonaws.com/beta/arduino-id/";
char resource[]="/beta/arduino-id";
String postData;
String postVariable="id:";

unsigned long time2=0;
int prev;
long debug=200;
unsigned long prevtime;
unsigned long a=0;
String id="4545454uno:1";
void setup()
{
Serial.begin(115200);
pinMode(switchs,INPUT);
pinMode(light,OUTPUT);
WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
WiFi.begin(ssid,pass);
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.print("Attempting to connect to Network named:");
  Serial.println(ssid);
WiFi.begin(ssid,pass);
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
        a=time2-prevtime;
        float sa=a/1000000;
        //Serial.print(a);
        //Serial.println();
        StaticJsonBuffer<200> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        root["id"]=id;
        root["status"]="on";
        root["time in seconds"]=sa;
        char jsonchar[200];
        root.printTo((char*)jsonChar, root.measureLength() + 1);
        if(WiFi.status()==WL_CONNECTED)
        {
          root.printTo(Serial);
          HTTPClient http;
          http.begin(host);
          http.addHeader("Content-Type" ,"application/json");
          int httpCode=http.POST(jsonchar);
          String payload=http.getString();
          Serial.println(httpCode);
          Serial.println("payload");
        prevtime=micros();
    }
    }
   else if(sws==HIGH && prev!=sws)
   {
    prevtime=micros();
    }
    
    
    prev=sws;
    time2=micros();
    delay(50);
     

}
