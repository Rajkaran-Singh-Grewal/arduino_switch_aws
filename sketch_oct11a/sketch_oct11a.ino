#define switchs 12
#define light 13
int sws;
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
}
void loop()
{
  sws=digitalRead(switchs);
    if(sws==HIGH){digitalWrite(light,HIGH);}
    else{digitalWrite(light,LOW);}
    if(sws==LOW && prev!=sws )
    {
        digitalWrite(light,HIGH);
        Serial.print(id+",on");
        Serial.print(",");
        a=time-prevtime;
        Serial.print(a);
        Serial.println();   
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
