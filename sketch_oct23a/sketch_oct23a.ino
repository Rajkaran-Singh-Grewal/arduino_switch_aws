#include<ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

char ssid[]="Binatone";
char pass[]="Grewalfamily999";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
WiFi.begin(ssid, pass);
 
while (WiFi.status() != WL_CONNECTED) {
 
delay(1000);
Serial.print("Connecting..");
 
}
 
}


void loop() {
  // put your main code here, to run repeatedly:
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload
Serial.println(payload);                     //Print the response payload
 
}
 
http.end();   //Close connection
 
}
 
delay(30000);    //Send a request every 30 seconds
 
}
