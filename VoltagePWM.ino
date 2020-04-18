#include <Adafruit_MCP4725.h>
#include <Wire.h>
Adafruit_MCP4725 dac; //constructor

char c;
String com;
String targetstr;
String actualstr;
bool newdata = true;
float target;
float actual;
float diff;
int pwm = 2048;
float firstup = 2.75;
float firstdown = 2.25;
float intensifier = 5;
unsigned long lasttime = 0;
unsigned long currenttime = 0;
int watchdog = 1000;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
dac.begin(0x60);
}



void loop() {
  // put your main code here, to run repeatedly:
currenttime = millis();
  
while(Serial.available()>0&&newdata == true){
  c = Serial.read();

  if(c =='\n'){
  targetstr = com.substring(0,com.indexOf(","));
  target = targetstr.toFloat();
  actualstr = com.substring(com.indexOf(",")+1);
  actual = actualstr.toFloat();
  com = "";//reset string
  diff = actual - target;
  newdata = false; //reset flag
  lasttime = currenttime;
  //Serial.println(diff);
  }
  else{
    com += c;
  }
 
}
if(diff>0){
  pwm = (((2.75+(2.75*(diff/intensifier)))/5)*4096); //set pwm
  //if statements take care of out of bounds pwm number
  if(pwm<(firstup/5)*4096){
    pwm=firstup*4096;
  }
  if(pwm>.85*4096){
    pwm=4096*.85;
  }
  
}
if(diff<=0){
  pwm = (((2.25+(2.25*(diff/intensifier)))/5)*4096);
  if(pwm>(firstdown/5)*4096){
    pwm=firstdown*4096;
    }
  if(pwm<.15*4096){
    pwm=4096*.15;
  }
  
}
if(newdata == false){
dac.setVoltage(pwm,false);
//Serial.println(pwm);
newdata = true;
}

//watchdog reset
if(currenttime - lasttime > watchdog){
  dac.setVoltage(2048,false);
}


}


















 
