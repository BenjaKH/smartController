/*
 * Project: WEMO
 * Description: Control smart lighting switch from a button
 * Author: benjamin hansen
 * Date: 07/17/20
 */

 // Connect Ethernet port per Fritzing diagram and a button to Pin 23 (with pulldown resistor)
 // The functions switchOn(wemo) and switchOff(wemo) take an int and turn on the corresponding Wemo in the classroom
 // Please make sure to move the wemo library folder into your Arduino libraries directory

#include <Ethernet.h>
#include <SPI.h>
#include <mac.h>
#include <wemo.h> 
#include <Encoder.h>
#include <OneButton.h>

Encoder myEnc(14, 15);
OneButton button1(23, true, true);
int wemo[] = {0, 1, 2 ,3};
int c = 0;
int pos, old_pos, pos2, newVal;
bool laststate, buttonState, state;


void setup(){
  button1.attachClick(click1);
  button1.setDebounceTicks(100);
  
  Serial.begin(9600);
  Ethernet.begin(mac);
  delay(1000);
  Serial.println("connecting...");

  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();

  c = 0;
  buttonState = false;
  laststate = true;
  state = false;
}

void loop(){
  button1.tick();
  
  pos = myEnc.read();
  if (pos > 96){
    pos = 96; 
    myEnc.write(96);  
      }
  if (pos < 0){
    pos = 0;
    myEnc.write(0);
      }
  c = map(pos, 0, 96, 0, 3);
  Serial.printf("%i C \n", c);

  if (buttonState != laststate){     
    laststate = buttonState;
      }
 }

void click1(){
  Serial.println("Click");
  state = !state; 
       if (state == true){
      switchON(wemo[c]);}
     else{
       switchOFF(wemo[c]);
    Serial.printf("i% Click \n", c);  
 }}
