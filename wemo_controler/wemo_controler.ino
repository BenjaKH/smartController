

#include <Ethernet.h>
#include <SPI.h>
#include <mac.h>
#include <wemo.h> 
#include <Encoder.h>
#include <OneButton.h>
IPAddress ip(192,168,1,16);
Encoder myEnc(14, 15);
OneButton button1Wemo(23, true, true);
int wemo[] = {0, 1, 2 ,3};
int Z = 0;
int posW, old_posW, pos2W, newValW;
bool laststateW, buttonStateW, stateW;


void setup(){

  initWemoButtons();
  initethernet();
  initWemoSetup();

}

void loop(){
  button1Wemo.tick();
  

  WhichOutlet();
  WemoFunction();
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

 void initethernet(){
  Serial.begin(9600);
  Ethernet.begin(mac,ip);
  delay(2000);              // Wait for Serial Monitor
  Serial.println("connecting...");
  Serial.println(Ethernet.linkStatus());
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
    }
  Serial.println();
  Serial.print("LinkStatus: ");
}

void initWemoSetup(){
    Z = 0;
  buttonStateW = false;
  laststateW = true;
  stateW = false;
}

void initWemoButtons(){
  button1Wemo.attachClick(click1Wemo);
  button1Wemo.setDebounceTicks(100);
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
  Serial.printf("%i Z \n", Z);
} 
