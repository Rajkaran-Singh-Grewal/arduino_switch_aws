#include<ESP8266HTTPClient.h>
#include<ESP8266WiFi.h>
#include<WiFiClientSecure.h>
#include<ArduinoJson.h>
#define switchs D7
#define light D0
const char* ssid = "Binatone";
const char* pass="Grewalfamily999";
int sws;
char jsonChar[200];
char host[]="https://7676hssfl5.execute-api.us-east-2.amazonaws.com/beta";
char resource[]="/arduino-id";
String postData;
String postVariable="id:";
char fingerprint[]="98:F8:5E:FC:11:01:03:4F:0F:C1:1E:FE:E9:81:C9:9C:C8:43:27:4C";
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
WiFi.mode(WIFI_OFF);
delay(1000);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, pass);
Serial.print("Connecting");
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print(".");
 
}
 Serial.println("Wifi Connected");
 Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void loop()
{
  WiFiClientSecure https;
  https.setFingerprint(fingerprint);
        https.setTimeout(15000);
        delay(1000);
  sws=digitalRead(switchs);
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!https.connect(host, 443)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
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
        
        root.printTo((char*)jsonChar, root.measureLength() + 1);
        
        
   
      Serial.println(jsonChar);
     https.print(String("POST ")+resource+" HTTP/1.1\r\n"+"Host: "+host+ "\r\n"+"Content-Type: application/json" +"\r\n"+jsonChar+" Content-Length: 124"+"\r\n\n"+"Connection: close\r\n\r\n");
      Serial.println("request sent");
                  
  while (https.connected()) {
    Serial.print("1.");
    String line = https.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
 
  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(https.available()){        
    line = https.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
  Serial.println("==========");
  Serial.println("closing connection");
        prevtime=micros();
    
    }
   else if(sws==HIGH && prev!=sws)
   {
    prevtime=micros();
    }
    
    
    prev=sws;
    time2=micros();
    delay(50);
     

}
