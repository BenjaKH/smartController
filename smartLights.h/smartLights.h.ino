/*

 * Project: Using OneButton library / oneButtonArray

 * Description: Use oneButton and arrays

 * Author: Benjamin Hansen

 * Date: 7/13/20

 */
#include <SPI.h>
#include <Ethernet.h>
#include <mac.h>
#include <hue.h>
#include <Encoder.h>
#include <colors.h> 
#include <OneButton.h>
OneButton button1(23, true, true); 
int buttonPin = 23;
int i, j;
boolean activated;  // true for bulb on, falso for off

bool buttonstate, laststate, hueState; 
int lasti;
int lastbright, lastbulb;
int bright, pos, newVal;
Encoder myEnc(14, 15); 
IPAddress ip(192,168,1,16);  // Teensy IP
int colorArray[] = {HueRed, HueOrange, HueYellow, HueGreen, HueBlue, HueIndigo, HueViolet};
int bulb[] = {0, 1, 2, 3, 4};

void setup() {
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleClick1);
  button1.attachLongPressStop(longPress1);
  button1.setDebounceTicks(100);

  Serial.begin(9600);
  Ethernet.begin(mac,ip);
  delay(2000);              // Wait for Serial Monitor
  Serial.print("LinkStatus: ");
  Serial.println(Ethernet.linkStatus());

//  pinMode(buttonPin,INPUT);
//  delay(2000);
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

void loop() {
  button1.tick();
  
  pos = myEnc.read();
  if (pos > 255){
    pos = 255;
    myEnc.write(255);   
      }
  if (pos < 0){
   pos = 0;
    }
  bright = pos;
//Serial.println(pos);
  

  if((hueState!=laststate)||(bright != lastbright) || (i != lasti) || (j != lastbulb)){
    setHue(bulb[j], hueState, colorArray[i], bright);
    laststate = hueState;
    lastbright = bright;
    lasti = i;
    lastbulb = j;
    Serial.printf("%i bulb value \n", j);
    
  }
    
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
  Serial.printf("DoubleClick: %i \n",i);
}

void longPress1(){j
  j++;
  if(j>5){
    j=1;
    }
    Serial.printf("%i position of light \n", j);
}

void smartLights(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Smart Lights \n, Bulb %i", j);

  display.display();
  delay(5000);
}
