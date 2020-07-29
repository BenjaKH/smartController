#include "libraries.h"

OneButton GreenButton(21, false, true);

const int green_led = 12;
const int red_led = 4;
int GreenButtonState[] = {0, 1, 2, 3};
int G = 1;
//bool flash = false; 

void setup() {
  initGreenButton();
  initButtonLights();
  initethernet();
  initLightsSetup();
}

void loop() {
  button1.tick();
  GreenButton.tick();
  Serial.printf("%i \n", G);

  while (G== 0){
    button1.tick();
    GreenButton.tick();
    Brightness();
    BulbFunction();
  }
}
void clickGB(){
  GreenButtonState[G];
  G++;
  if (G > 4){
    G=0;
  }
}
void doubleclickGB(){
  
  Serial.printf("Double Click %i \n");
  
}

void initGreenButton() {
  GreenButton.attachClick(clickGB);
  GreenButton.attachDoubleClick(doubleclickGB);
}
void click1Lights(){
  Serial.println("Click");
  hueState = !hueState;
}

void doubleClick1Lights(){
  Serial.println("DoubleClick");
  x++;
  if (x > 7) {
    x=0;
    }
}

void longPress1Lights(){
  y++;
  if(y>5){
    y=1;
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
  x=2;
  y=1;
  setHue(bulb[y], true, colorArrayHue[x], bright);
  buttonstate = true; 
  laststate = false;
  hueState = true;
  lastx = x;
  lastbright = bright;
  lastbulb = y;
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
  if((hueState!=laststate)||(bright != lastbright) || (x != lastx) || (y != lastbulb)){
    setHue(bulb[y], hueState, colorArrayHue[x], bright);
    laststate = hueState;
    lastbright = bright;
    lastx = x;
    lastbulb = y;
      if (hueState == true){
       a = "ON";
        }
      else{
        a = "OFF";
          }
    Serial.printf("Bulb %i is %s, Color Value = %i, Brightness %i\n",  y, a, colorArrayHue[x], bright);
    } 
}
