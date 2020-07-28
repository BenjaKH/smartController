#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_SSD1306.h>
#include <colors.h>
#include <Encoder.h>
#include <Ethernet.h>
#include <hue.h>
#include <mac.h>
#include <OneButton.h>
#include <SPI.h>
#include <SD.h>
#include <wemo.h> 
#include <Wire.h>

IPAddress ip(192,168,1,16);
Adafruit_NeoPixel pixel(12, 16, NEO_GRB + NEO_KHZ800);
Encoder myEnc(14, 15);
OneButton button1(23, true, true);

int wemo[] = {0, 1, 2 ,3};
int Z = 0;
int p = 0;
int pinOut = 16;
int buttonPin = 23;
int colorArrayHue[] = {HueRed, HueOrange, HueYellow, HueGreen, HueBlue, HueIndigo, HueViolet};
int colorArray[] = {violet, blue, purple, cyan, teal, green, yellow, orange, maroon, red};
int bulb[] = {0, 1, 2, 3, 4};
bool status = true;

int posW, old_posW, pos2W, newValW, newVal, j,  lastbright, lastbulb, lastx, bright, pos, newVal, x, y;
bool laststateW, buttonStateW, stateW, buttonstate, laststate, hueState, activated;
float humidRH, pressPA, tempC, tempF, hpa, inHg;

byte i;
byte count = 0;