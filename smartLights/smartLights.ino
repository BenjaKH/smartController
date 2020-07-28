
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


void setup() {
  initButtonLights();
  initethernet();
  initLightsSetup();  

}

void loop() {
  button1.tick();
  
  Brightness();
  BulbFunction();
    
}

void click1Lights(){
  Serial.println("Click");
  hueState = !hueState;
}

void doubleClick1Lights(){
  Serial.println("DoubleClick");
  i++;
  if (i > 7) {
    i=0;
    }
}

void longPress1Lights(){
  j++;
  if(j>5){
    j=1;
    }
}

void initButtonLights(){
  button1.attachClick(click1Lights);
  button1.attachDoubleClick(doubleClick1Lights);
  button1.attachLongPressStop(longPress1Lights);
  button1.setDebounceTicks(100);
}

void initethernet(){
  Serial.begin(9600);
  Ethernet.begin(mac,ip);
  delay(2000);              // Wait for Serial Monitor
  Serial.println("connecting...");
  Serial.println(Ethernet.linkStatus());
    // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  Serial.print("LinkStatus: ");
}

void initLightsSetup() {
  Serial.println(" Ready.");
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
  char *a = "ON";
  if((hueState!=laststate)||(bright != lastbright) || (i != lasti) || (j != lastbulb)){
    setHue(bulb[j], hueState, colorArray[i], bright);
    laststate = hueState;
    lastbright = bright;
    lasti = i;
    lastbulb = j;
      if (hueState == true){
       a = "ON";
        }
      else{
        a = "OFF";
          }
    Serial.printf("Bulb %i is %s, Color Value = %i, Brightness %i\n",  j, a, colorArray[i], bright);
    } 
}
