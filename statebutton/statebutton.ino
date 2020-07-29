#include "OneButton.h"
OneButton GreenButton(21, false, true);

const int green_led = 12;
const int red_led = 4;
int GreenButtonState[] = {0, 1, 2, 3};
int G;
//bool flash = false; 

void setup() {
initGreenButton();

}

void loop() {
  GreenButton.tick();
  Serial.printf("%i \n", G);
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
