#include "libraries.h"
Timer timer;

OneButton GreenButton(21, false, true);

const int green_led = 12;
const int red_led = 4;
int GreenButtonState[] = {0, 1, 2, 3};
int G = 0;



void setup() {
 initeverything();

}

void loop() {
  button1.tick();
  GreenButton.tick();
  Serial.printf("%i \n", G);

  while (G==0){
   whileBME();
  }
  while (G== 1){
    whileSmartLights();
  }
  while (G==2){
    whileOutlets();
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
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Bulb %i is %s, Brightness %i\n", y, a, bright);
  display.display();
}}
void testdrawstyles(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("Hello, world!"));

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text

  display.setTextSize(2);             // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);

  display.display();
  delay(2000);
}

void drawreadBME(void) {
  static int t = 0;
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  if (t == 0){
    display.printf("Atomspheric pressure is %.2f inches mercury. \n", inHg);
  }
  if (t == 1){
    display.printf("Humidity is %.2f percent. \n", humidRH);
  }
  if (t == 2){
    display.printf("Temperature right now is %.2f , F. \n", tempF);
  }
  display.display();
    t++;
    if (t > 2){
    t = 0; 
  }
}

void initDisplay() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void initPixel() {
  pixel.begin();
  pixel.show();
  pixel.setBrightness(10);
}

void pixel2temp() {
  newVal = map(tempF, 70, 90, 0, 12);
  pixel.fill(colorArray[newVal], 0, 12);
  pixel.show();
  pixel.setBrightness(10);
}

void StatusBME() {
  status = bme.begin(0x76);
  if(status == false){
    Serial.print("Error");
      }
}

float CtoF(float IN) {
  return (IN * 1.8) + 32;
}

float PressCon(float P){
  return (0.03 * P);
}

void click1Wemo(){
  Serial.println("Click");
  stateW = !stateW; 
       if (stateW == true){
      switchON(wemo[Z]);}
     else{
       switchOFF(wemo[Z]);
    Serial.printf("i% Click \n", Z);  
        }
}
void initWemoSetup(){
    Z = 0;
  buttonStateW = false;
  laststateW = true;
  stateW = false;
}

void initWemoButtons(){
  button1.attachClick(click1Wemo);
  button1.setDebounceTicks(100);
}

void WemoFunction(){
    if (buttonStateW != laststateW){     
    laststateW = buttonStateW;
      }
}

void WhichOutlet(){
  posW = myEnc.read();
  if (posW > 96){
    posW = 96; 
    myEnc.write(96);  
      }
  if (posW < 0){
    posW = 0;
    myEnc.write(0);
      }
  Z = map(posW, 0, 96, 0, 3);
   if (stateW == true){
       o = "ON";
        }
      else{
        o = "OFF";
          }
  Serial.printf("%i Z \n", Z);
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Outlet %i is %s\n", Z, o);
  display.display();
} 

void initeverything(){
      Serial.begin(9600);
  while (!Serial);          
    Serial.print("Initializing..."); 
  initGreenButton();
  initButtonLights();
  initethernet();
  initLightsSetup();
  initDisplay(); 
  initPixel();
  StatusBME();  
  testdrawstyles();
  drawreadBME();
  timer.startTimer(4000);
  initWemoButtons();
  initWemoSetup();
}

void whileBME(){
      button1.tick();
    GreenButton.tick();
    pressPA = bme.readPressure() / 100.0F;
    inHg = PressCon(pressPA);
    humidRH = bme.readHumidity();
    tempC = bme.readTemperature();
    tempF = CtoF(tempC);
    if (timer.isTimerReady() == true){
      drawreadBME(); 
      timer.startTimer(4000);
    } 
    pixel2temp();
    Serial.printf("%i \n", G);
}

void whileSmartLights(){
  button1.tick();
  GreenButton.tick();
  Brightness();
  BulbFunction();
}

void whileOutlets(){
  button1.tick();
  GreenButton.tick();
  WhichOutlet();
  WemoFunction();
}
