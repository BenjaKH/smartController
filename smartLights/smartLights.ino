
#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>
#include <hue.h>
#include <Encoder.h>
#include <colors.h> 
#include <OneButton.h>
OneButton button1(23, true, true); 
int buttonPin = 23;
boolean activated;  // true for bulb on, falso for off
bool buttonstate, laststate, hueState; 
int lastbright, lastbulb, lasti, bright, pos, newVal, i, j;
Encoder myEnc(14, 15); 
IPAddress ip(192,168,1,16);  // Teensy IP
int colorArray[] = {HueRed, HueOrange, HueYellow, HueGreen, HueBlue, HueIndigo, HueViolet};
int bulb[] = {0, 1, 2, 3, 4};

//String a;

void setup() {
  initbuttons();
  initethernet();
  initLightsSetup();  

}

void loop() {
  button1.tick();
  
  Brightness();
  BulbFunction();
    
}

void click1(){
  Serial.println("Click");
  hueState = !hueState;
}

void doubleClick1(){
  Serial.println("DoubleClick");
  i++;
  if (i > 7) {
    i=0;
    }
}

void longPress1(){
  j++;
  if(j>5){
    j=1;
    }
}

void initbuttons(){
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleClick1);
  button1.attachLongPressStop(longPress1);
  button1.setDebounceTicks(100);
}

void initethernet(){
  Serial.begin(9600);
  Ethernet.begin(mac,ip);
  delay(2000);              // Wait for Serial Monitor
  Serial.print("LinkStatus: ");
  Serial.println(Ethernet.linkStatus());
}

void initLightsSetup() {
  Serial.println("Ready.");
  i=2;
  j=1;
  setHue(bulb[j], true, colorArray[i], bright);
  buttonstate = true; 
  laststate = false;
  hueState = true;
  lasti = i;
  lastbright = bright;
  lastbulb = j;
}

void Brightness() {
    pos = myEnc.read();
  if (pos > 255){
    pos = 255;
    myEnc.write(255);   
      }
  if (pos < 0){
   pos = 0;
    }
  bright = pos;
}

void BulbFunction() {
  if((hueState!=laststate)||(bright != lastbright) || (i != lasti) || (j != lastbulb)){
    setHue(bulb[j], hueState, colorArray[i], bright);
    laststate = hueState;
    lastbright = bright;
    lasti = i;
    lastbulb = j;
//      if (hueState == true){
//       a = "ON";
//        }
//      else{
//        a = "OFF";
//          }
    Serial.printf("Bulb %i is %i, Color Value = %i, Brightness %i\n",  j, hueState, colorArray[i], bright);
    } 
}
