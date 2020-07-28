#include <Adafruit_BME280.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <colors.h>

Adafruit_NeoPixel pixel(12, 16, NEO_GRB + NEO_KHZ800);
int p = 0;
int pinOut = 16;
int newVal, j;
int colorArray[] = {violet, blue, purple, cyan, teal, green, yellow, orange, maroon, red};
byte i;
byte count = 0;
float humidRH, pressPA, tempC, tempF, hpa, inHg;
bool status = true;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET    
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  while (!Serial);          
    Serial.print("Initializing..."); 

  initDisplay(); 
  initPixel();
  StatusBME();  
  testdrawstyles();
  drawreadBME();
}


void loop() {

 // this code sets up my BME 
  pressPA = bme.readPressure() / 100.0F;
  inHg = PressCon(pressPA);
  humidRH = bme.readHumidity();
  tempC = bme.readTemperature();
  tempF = CtoF(tempC);

  drawreadBME(); 
  pixel2temp();
}

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
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Atomspheric pressure is %.2f inches mercury. \n", inHg);
  display.display();
  delay(5000);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("Humidity is %.2f percent. \n", humidRH);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.display();
  delay(5000);
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.printf("Temperature right now is %.2f , F. \n", tempF);
  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
  display.display();
  delay(4000);
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
