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
int newVal;
int colorArray[] = {violet, blue, purple, cyan, teal, green, yellow, orange, maroon, red};


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };



Adafruit_BME280 bme;

byte i;
byte count = 0;
float humidRH, pressPA, tempC, tempF, hpa, inHg;
bool status = true;

const int readArray[] = {14, 15, 16};
String dataString;
int j;
int num_sensors;
float sensor;

void setup() {
Serial.begin(9600);

   while (!Serial);          
  Serial.print("Initializing..."); 
  
//  num_sensors = 3;

//   SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawPixel(10, 10, SSD1306_WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();
  delay(2000);
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  testdrawstyles();    // Draw 'stylized' characters
  drawreadpressure(); //
  drawreadHumidity();
  drawreadTemperature();

  
  // Invert and restore display, pausing in-between
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);

  while (!Serial);
  Serial.printf("Beginning I2C scan \n");

  
 status = bme.begin(0x76);
 if(status == false){
 Serial.print("Error");}

 pixel.begin();
 pixel.show();
 pixel.setBrightness(10);
}


void loop() {
 
  pressPA = bme.readPressure() / 100.0F;
  inHg = (0.03 * pressPA);
//  Serial.printf("Atomspheric pressure is %.2f inches mercury. \n", inHg);
//  delay(5000);
  
  humidRH = bme.readHumidity();
//  Serial.printf("Humidity is %.2f percent. \n", humidRH);
//  delay(5000);

  tempC = bme.readTemperature();
  tempF = ((tempC * 1.8) + 32);
//  Serial.printf("Temperature right now is %.2f , F. \n", tempF);
//  delay(5000);

  drawreadpressure(); //
  drawreadHumidity();
  drawreadTemperature();

  // clear thestring for assembling the data to log:
  dataString = "";


  Serial.println("About to collect data from sensors");
  delay(2000);
  // read three sensors and append to the string:
//  for (j = 0; j < num_sensors; j++) {
//    sensor = random(0,1047);
    dataString += String("Pressure, ");
    dataString += String(inHg);
    dataString += String(", Humidy, " );
    dataString += String(humidRH);
    dataString += String(", TempF, " );
    dataString += String(tempF);


  newVal = map(tempF, 70, 90, 0, 12);
    pixel.fill(colorArray[newVal], 0, 12);
    pixel.show();


  pixel.setBrightness(10);
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

void drawreadpressure(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Atomspheric pressure is %.2f inches mercury. \n", inHg);

  display.display();
  delay(5000);
}
void drawreadHumidity(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Humidity is %.2f percent. \n", humidRH);

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text

  display.display();
  delay(5000);
}
void drawreadTemperature(void) {
  display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.printf("Temperature right now is %.2f , F. \n", tempF);

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text

  display.display();
  delay(2000);
}
